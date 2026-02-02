package logic

import (
	"context"
	"swe3/file_analyzer/internal/db"
	"swe3/file_analyzer/internal/domain"
	filestorer "swe3/file_analyzer/internal/file_storer"
	"swe3/library/go/usecase"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PublicValueInstance
type ListReportsArgs struct {
	WorkName string
}

// @PublicValueInstance
type ListReportsRes struct {
	Reports []domain.Report
}

type ListReportsUsecase = usecase.Usecase[ListReportsArgs, ListReportsRes]

// @PublicPointerInstance
type listReportsUsecase struct {
	db         db.Adapter
	fileStorer filestorer.Adapter
}

var _ ListReportsUsecase = (*listReportsUsecase)(nil)

func (uc *listReportsUsecase) Execute(ctx context.Context, args ListReportsArgs) (ListReportsRes, error) {
	reports, err := uc.db.SelectReports(ctx, args.WorkName)
	if err != nil {
		return ListReportsRes{}, err
	}

	return NewListReportsRes(reports), nil
}
