package storage

import (
	"bytes"
	"context"

	minio "github.com/minio/minio-go/v7"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

type Adapter interface {
	PutObject(ctx context.Context, objectID string, object []byte) error
	GetObject(ctx context.Context, objectID string) ([]byte, error)
}

var _ Adapter = (*adapter)(nil)

// @PublicPointerInstance
type adapter struct {
	client *minio.Client
}

func (a *adapter) PutObject(ctx context.Context, objectID string, object []byte) error {
	_, err := a.client.PutObject(
		ctx,
		defaultBucket,
		objectID,
		bytes.NewReader(object),
		int64(len(object)),
		minio.PutObjectOptions{},
	)

	return err
}

func (a *adapter) GetObject(ctx context.Context, objectID string) ([]byte, error) {
	object, err := a.client.GetObject(
		ctx,
		defaultBucket,
		objectID,
		minio.GetObjectOptions{},
	)
	if err != nil {
		return nil, err
	}
	defer object.Close()

	buf := new(bytes.Buffer)
	if _, err := buf.ReadFrom(object); err != nil {
		return nil, err
	}

	return buf.Bytes(), nil
}
