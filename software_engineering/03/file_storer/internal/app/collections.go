package app

import (
	"swe3/file_storer/internal/db"
	"swe3/file_storer/internal/grpc"
	"swe3/file_storer/internal/http"
	"swe3/file_storer/internal/logic"
	"swe3/file_storer/internal/storage"
	"swe3/file_storer/internal/telemetry"

	"github.com/leshless/golibrary/graceful"

	interrupter "github.com/leshless/golibrary/interrupter"
)

//go:generate go run github.com/leshless/golibrary/constructor_generator

// @PrivateValueInstance
type dependencies struct {
	interrupter        interrupter.Interrupter
	gracefulTerminator graceful.Terminator
	logger             telemetry.Logger
}

// @PrivateValueInstance
type adapteres struct {
	db      db.Adapter
	storage storage.Adapter
}

// @PrivateValueInstance
type usecases struct {
	createSubmission    logic.CreateSubmissionUsecase
	listWorkSubmissions logic.ListWorkSubmissionsUsecase
}

// @PrivateValueInstance
type ports struct {
	http http.Port
	grpc grpc.Port
}
