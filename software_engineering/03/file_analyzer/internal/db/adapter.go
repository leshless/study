package db

import (
	"context"
	"encoding/json"
	"fmt"
	"swe3/file_analyzer/internal/db/queries"
	"swe3/file_analyzer/internal/domain"
	"swe3/library/go/xsql"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

type Adapter interface {
	InsertReport(ctx context.Context, report domain.Report) error
	SelectReports(ctx context.Context, workName string) ([]domain.Report, error)
}

var _ Adapter = (*adapter)(nil)

// @PublicPointerInstance
type adapter struct {
	client xsql.Client
}

func (a *adapter) InsertReport(ctx context.Context, report domain.Report) error {
	similarSubmissionIDsJSON, err := json.Marshal(report.SimilarSubmissionIDs)
	if err != nil {
		return fmt.Errorf("marshalling similar submissions json: %w", err)
	}

	_, err = a.client.Exec(
		ctx,
		queries.InsertReport,
		report.ID,
		report.WorkName,
		report.SubmissionID,
		report.OriginalityPercent,
		similarSubmissionIDsJSON,
		report.CreatedTime,
	)

	return err
}

func (a *adapter) SelectReports(ctx context.Context, workName string) ([]domain.Report, error) {
	rows, err := a.client.Query(ctx, queries.SelectReports, workName)
	if err != nil {
		return nil, err
	}
	defer rows.Close()

	var reports []domain.Report
	for rows.Next() {
		var report domain.Report
		var similarSubmissionIDsJSON []byte

		if err := rows.Scan(
			&report.ID,
			&report.WorkName,
			&report.SubmissionID,
			&report.OriginalityPercent,
			&similarSubmissionIDsJSON,
			&report.CreatedTime,
		); err != nil {
			return nil, err
		}

		if err := json.Unmarshal(similarSubmissionIDsJSON, &report.SimilarSubmissionIDs); err != nil {
			return nil, fmt.Errorf("unmarshalling similar submissions json: %w", err)
		}

		reports = append(reports, report)
	}

	return reports, nil
}
