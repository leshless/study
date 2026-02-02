package logic

import (
	"context"
	"swe3/file_storer/internal/db"
	"swe3/file_storer/internal/domain"
	"swe3/file_storer/internal/storage"
	"swe3/library/go/usecase"
	"time"

	"github.com/google/uuid"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PublicValueInstance
type CreateSubmissionArgs struct {
	WorkName    string
	StudentName string
	File        []byte
}

// @PublicValueInstance
type CreateSubmissionRes struct {
	SubmissionID string
}

type CreateSubmissionUsecase = usecase.Usecase[CreateSubmissionArgs, CreateSubmissionRes]

// @PublicPointerInstance
type createSubmissionUsecase struct {
	db      db.Adapter
	storage storage.Adapter
}

var _ CreateSubmissionUsecase = (*createSubmissionUsecase)(nil)

func (uc *createSubmissionUsecase) Execute(ctx context.Context, args CreateSubmissionArgs) (CreateSubmissionRes, error) {
	objectID := uuid.NewString()

	if err := uc.storage.PutObject(ctx, objectID, args.File); err != nil {
		return CreateSubmissionRes{}, err
	}

	submissionID := uuid.NewString()

	submission := domain.NewSubmission(
		submissionID,
		args.WorkName,
		args.StudentName,
		objectID,
		time.Now(),
	)

	if err := uc.db.InsertSubmission(ctx, submission); err != nil {
		return CreateSubmissionRes{}, err
	}

	return CreateSubmissionRes{
		SubmissionID: submissionID,
	}, nil
}
