package db

import (
	"context"
	"swe3/file_storer/internal/db/queries"
	"swe3/file_storer/internal/domain"
	"swe3/library/go/xsql"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

type Adapter interface {
	InsertSubmission(ctx context.Context, submission domain.Submission) error
	SelectSubmission(ctx context.Context, submissionID string) (domain.Submission, error)
	SelectWorkSubmissions(ctx context.Context, workName string) ([]domain.Submission, error)
}

var _ Adapter = (*adapter)(nil)

// @PublicPointerInstance
type adapter struct {
	client xsql.Client
}

func (a *adapter) InsertSubmission(ctx context.Context, submission domain.Submission) error {
	_, err := a.client.Exec(
		ctx,
		queries.InsertSubmission,
		submission.ID,
		submission.WorkName,
		submission.StudentName,
		submission.ObjectID,
		submission.CreatedTime,
	)

	return err
}

func (a *adapter) SelectSubmission(ctx context.Context, submissionID string) (domain.Submission, error) {
	rows, err := a.client.Query(
		ctx,
		queries.SelectSubmission,
		submissionID,
	)
	if err != nil {
		return domain.Submission{}, err
	}
	defer rows.Close()

	if !rows.Next() {
		return domain.Submission{}, domain.NewSubmissionNotFoundError()
	}

	var submission domain.Submission
	if err := rows.Scan(
		&submission.ID,
		&submission.WorkName,
		&submission.StudentName,
		&submission.ObjectID,
		&submission.CreatedTime,
	); err != nil {
		return domain.Submission{}, err
	}

	return submission, nil
}

func (a *adapter) SelectWorkSubmissions(ctx context.Context, workName string) ([]domain.Submission, error) {
	rows, err := a.client.Query(
		ctx,
		queries.SelectWorkSubmissions,
		workName,
	)
	if err != nil {
		return nil, err
	}
	defer rows.Close()

	var submissions []domain.Submission
	for rows.Next() {
		var submission domain.Submission
		if err := rows.Scan(
			&submission.ID,
			&submission.WorkName,
			&submission.StudentName,
			&submission.ObjectID,
			&submission.CreatedTime,
		); err != nil {
			return nil, err
		}
		submissions = append(submissions, submission)
	}

	if err := rows.Err(); err != nil {
		return nil, err
	}

	return submissions, nil
}
