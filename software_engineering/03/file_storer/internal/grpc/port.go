package grpc

import (
	"fmt"
	"net"
	"swe3/file_storer/internal/telemetry"

	"google.golang.org/grpc"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

type Port interface {
	Run() error
}

// @PublicPointerInstance
type port struct {
	grpcServer *grpc.Server
	logger     telemetry.Logger
}

var _ Port = (*port)(nil)

func (p *port) Run() error {
	lis, err := net.Listen("tcp", fmt.Sprintf(":%d", listenPort))
	if err != nil {
		return fmt.Errorf("failed to start listener: %w", err)
	}

	p.logger.Info("started grpc server")

	return p.grpcServer.Serve(lis)
}
