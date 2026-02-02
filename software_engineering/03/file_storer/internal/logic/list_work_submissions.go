package logic

import (
	"context"
	"swe3/file_storer/internal/db"
	"swe3/file_storer/internal/domain"
	"swe3/file_storer/internal/storage"
	"swe3/library/go/usecase"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PublicValueInstance
type ListWorkSubmissionsArgs struct {
	WorkName string
}

// @PublicValueInstance
type ListWorkSubmissionsRes struct {
	Submissions []domain.Submission
	Files       [][]byte
}

type ListWorkSubmissionsUsecase = usecase.Usecase[ListWorkSubmissionsArgs, ListWorkSubmissionsRes]

// @PublicPointerInstance
type listWorkSubmissionsUsecase struct {
	db      db.Adapter
	storage storage.Adapter
}

var _ ListWorkSubmissionsUsecase = (*listWorkSubmissionsUsecase)(nil)

func (uc *listWorkSubmissionsUsecase) Execute(ctx context.Context, args ListWorkSubmissionsArgs) (ListWorkSubmissionsRes, error) {
	submissions, err := uc.db.SelectWorkSubmissions(ctx, args.WorkName)
	if err != nil {
		return ListWorkSubmissionsRes{}, err
	}

	var files [][]byte
	for _, submission := range submissions {
		fileData, err := uc.storage.GetObject(ctx, submission.ObjectID)
		if err != nil {
			return ListWorkSubmissionsRes{}, err
		}
		files = append(files, fileData)
	}

	return ListWorkSubmissionsRes{
		Submissions: submissions,
		Files:       files,
	}, nil
}
