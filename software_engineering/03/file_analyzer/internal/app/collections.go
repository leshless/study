package app

import (
	"swe3/file_analyzer/internal/db"
	filestorer "swe3/file_analyzer/internal/file_storer"
	"swe3/file_analyzer/internal/http"
	"swe3/file_analyzer/internal/logic"
	"swe3/file_analyzer/internal/telemetry"

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
	db         db.Adapter
	fileStorer filestorer.Adapter
}

// @PrivateValueInstance
type usecases struct {
	createReport logic.CreateReportUsecase
}

// @PrivateValueInstance
type ports struct {
	http http.Port
}
