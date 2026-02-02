package filestorer

import (
	"fmt"
	"swe3/file_analyzer/internal/telemetry"
	filestorerapi "swe3/file_storer/api/grpc"

	_ "github.com/lib/pq"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

const (
	host = "file_storer"
	port = 50051
)

func InitAdapter(
	logger telemetry.Logger,
) (*adapter, error) {
	conn, err := grpc.NewClient(
		fmt.Sprintf("%s:%d", host, port),
		grpc.WithTransportCredentials(insecure.NewCredentials()),
	)
	if err != nil {
		return nil, fmt.Errorf("creating grpc client: %w", err)
	}

	client := filestorerapi.NewSubmissionsClient(conn)

	return NewAdapter(logger, client), nil
}
