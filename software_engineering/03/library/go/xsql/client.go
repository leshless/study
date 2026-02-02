package xsql

import (
	"context"
	"database/sql"
)

type Client interface {
	Ping(ctx context.Context) error
	Close(ctx context.Context) error
	Exec(ctx context.Context, query string, args ...any) (sql.Result, error)
	Query(ctx context.Context, query string, args ...any) (*sql.Rows, error)
}

type client struct {
	db *sql.DB
}

var _ Client = (*client)(nil)

func NewClient(db *sql.DB) *client {
	return &client{
		db: db,
	}
}

func (c *client) Ping(ctx context.Context) error {
	return c.db.PingContext(ctx)
}

func (c *client) Close(ctx context.Context) error {
	return c.db.Close()
}

func (c *client) Exec(ctx context.Context, query string, args ...any) (sql.Result, error) {
	return c.db.ExecContext(ctx, query, args...)
}

func (c *client) Query(ctx context.Context, query string, args ...any) (*sql.Rows, error) {
	return c.db.QueryContext(ctx, query, args...)
}
