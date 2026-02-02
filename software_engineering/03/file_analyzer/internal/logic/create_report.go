package logic

import (
	"context"
	"strings"
	"swe3/file_analyzer/internal/db"
	"swe3/file_analyzer/internal/domain"
	filestorer "swe3/file_analyzer/internal/file_storer"
	"swe3/library/go/usecase"
	"time"
	"unicode"

	"github.com/google/uuid"
	"github.com/leshless/golibrary/set"
	"github.com/leshless/golibrary/sets"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PublicValueInstance
type CreateReportArgs struct {
	WorkName     string
	SubmissionID string
}

// @PublicValueInstance
type CreateReportRes struct {
	Report domain.Report
}

type CreateReportUsecase = usecase.Usecase[CreateReportArgs, CreateReportRes]

// @PublicPointerInstance
type createReportUsecase struct {
	db         db.Adapter
	fileStorer filestorer.Adapter
}

const (
	minSimilarityPercentForFlagging = 80.0
)

var _ CreateReportUsecase = (*createReportUsecase)(nil)

func (uc *createReportUsecase) Execute(ctx context.Context, args CreateReportArgs) (CreateReportRes, error) {
	submissions, err := uc.fileStorer.ListWorkSubmissions(ctx, args.WorkName)
	if err != nil {
		return CreateReportRes{}, err
	}

	var (
		targetSubmission domain.Submission
		submissionFound  bool
	)

	for _, submission := range submissions {
		if submission.ID == args.SubmissionID {
			targetSubmission = submission
			submissionFound = true
			break
		}
	}

	if !submissionFound {
		return CreateReportRes{}, domain.NewSubmissionNotFoundError()
	}

	var (
		originalityPercentSum     float64
		comparedSubmissionsAmount int
		similarSubmissionIDs      = make([]string, 0)
	)

	for _, submission := range submissions {
		// From same student, dont compare
		if submission.StudentName == targetSubmission.StudentName {
			continue
		}

		// Newer submission, dont compare
		if targetSubmission.CreationTime.Before(submission.CreationTime) {
			continue
		}

		similarityPercent := uc.calculateSimilarity(targetSubmission.File, submission.File)

		if similarityPercent >= minSimilarityPercentForFlagging {
			similarSubmissionIDs = append(similarSubmissionIDs, submission.ID)
		}
		originalityPercentSum += 100.0 - similarityPercent
		comparedSubmissionsAmount++
	}

	var originalityPercent float64
	if comparedSubmissionsAmount > 0 {
		originalityPercent = originalityPercentSum / float64(comparedSubmissionsAmount)
	} else {
		originalityPercent = 100.0
	}

	report := domain.NewReport(
		uuid.NewString(),
		args.WorkName,
		args.SubmissionID,
		originalityPercent,
		similarSubmissionIDs,
		time.Now(),
	)

	if err := uc.db.InsertReport(ctx, report); err != nil {
		return CreateReportRes{}, err
	}

	return CreateReportRes{
		Report: report,
	}, nil
}

func (uc *createReportUsecase) calculateSimilarity(file1, file2 []byte) float64 {
	// Normalize texts
	text1 := normalizeText(string(file1))
	text2 := normalizeText(string(file2))

	if text1 == "" && text2 == "" {
		return 100.0
	}

	// Split by words
	words1 := strings.Fields(text1)
	words2 := strings.Fields(text2)

	if len(words1) == 0 || len(words2) == 0 {
		return 0
	}

	// Evaluate similarity using Jaccard index
	// https://en.wikipedia.org/wiki/Jaccard_index
	set1 := set.New[string]()
	set2 := set.New[string]()

	for _, word := range words1 {
		set1.Add(word)
	}

	for _, word := range words2 {
		set2.Add(word)
	}

	unionSet := sets.Union(set1, set2)
	intersectionSet := sets.Intersection(set1, set2)

	if len(unionSet) == 0 {
		return 0
	}

	return float64(len(intersectionSet)) / float64(len(unionSet)) * 100
}

func normalizeText(text string) string {
	text = strings.ToLower(text)

	var result strings.Builder
	for _, r := range text {
		if !unicode.IsPunct(r) {
			result.WriteRune(r)
		} else {
			result.WriteRune(' ') // заменяем на пробел
		}
	}
	text = result.String()

	text = strings.TrimSpace(text)

	return text
}
