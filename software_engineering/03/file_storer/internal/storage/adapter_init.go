package storage

import (
	"context"
	"fmt"
	"swe3/file_storer/internal/telemetry"

	_ "github.com/lib/pq"
	"github.com/minio/minio-go/v7"
	"github.com/minio/minio-go/v7/pkg/credentials"
)

const (
	host          = "file-storer-minio"
	port          = 9000
	user          = "user"
	password      = "password"
	useSSL        = false
	defaultBucket = "objects"
)

func InitAdapter(
	logger telemetry.Logger,
) (*adapter, error) {
	minioClient, err := minio.New(fmt.Sprintf("%s:%d", host, port), &minio.Options{
		Creds:  credentials.NewStaticV4(user, password, ""),
		Secure: useSSL,
	})
	if err != nil {
		return nil, fmt.Errorf("initializing client: %w", err)
	}

	if err := ensureDefaultBucket(minioClient); err != nil {
		return nil, fmt.Errorf("ensuring default bucket: %w", err)
	}

	return NewAdapter(minioClient), nil
}

func ensureDefaultBucket(minioClient *minio.Client) error {
	defaultBucketExists, err := minioClient.BucketExists(context.Background(), defaultBucket)
	if err != nil {
		return fmt.Errorf("checking for default bucket: %w", err)
	}

	if defaultBucketExists {
		return nil
	}

	if err := minioClient.MakeBucket(context.Background(), defaultBucket, minio.MakeBucketOptions{}); err != nil {
		return fmt.Errorf("creating default bucket")
	}

	return nil
}
