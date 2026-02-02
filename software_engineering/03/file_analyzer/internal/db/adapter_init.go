package db

import (
	"context"
	"database/sql"
	"fmt"
	"swe3/file_analyzer/internal/db/mirgrations"
	"swe3/file_analyzer/internal/telemetry"
	"swe3/library/go/xsql"

	_ "github.com/lib/pq"
)

const (
	driverName = "postgres"
	host       = "file_analyzer_postgres"
	port       = 5432
	user       = "user"
	password   = "password"
	db         = "file_analyzer"
	sslMode    = "disable"
)

func InitAdapter(
	logger telemetry.Logger,
) (*adapter, error) {
	connectionString := fmt.Sprintf(
		"host=%s port=%d user=%s password=%s dbname=%s sslmode=%s",
		host,
		port,
		user,
		password,
		db,
		sslMode,
	)

	db, err := sql.Open(driverName, connectionString)
	if err != nil {
		return nil, fmt.Errorf("opening database connection: %w", err)
	}

	client := xsql.NewClient(db)

	if err = applyMirgations(client); err != nil {
		return nil, fmt.Errorf("applying migrations: %w", err)
	}

	if err = client.Ping(context.Background()); err != nil {
		return nil, fmt.Errorf("pinging database: %w", err)
	}

	return NewAdapter(client), nil
}

func applyMirgations(client xsql.Client) error {
	for i, migration := range mirgrations.Migrations {
		_, err := client.Exec(context.Background(), migration)
		if err != nil {
			return fmt.Errorf("applying migration %d: %w", i+1, err)
		}
	}

	return nil
}
