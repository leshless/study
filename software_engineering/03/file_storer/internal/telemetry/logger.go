package telemetry

import (
	"github.com/leshless/golibrary/xslices"

	"go.uber.org/zap"
)

type Logger interface {
	Debug(message string, fields ...Field)
	Info(message string, fields ...Field)
	Warn(message string, fields ...Field)
	Error(message string, fields ...Field)

	With(fields ...Field) Logger
}

type logger struct {
	zapLogger *zap.Logger
}

var _ Logger = (*logger)(nil)

func NewLogger(zapLogger *zap.Logger) *logger {
	return &logger{
		zapLogger: zapLogger,
	}
}

func (l *logger) Debug(message string, fields ...Field) {
	l.zapLogger.Debug(message, xslices.Map(fields, fieldToZap)...)
}

func (l *logger) Info(message string, fields ...Field) {
	l.zapLogger.Info(message, xslices.Map(fields, fieldToZap)...)
}

func (l *logger) Warn(message string, fields ...Field) {
	l.zapLogger.Warn(message, xslices.Map(fields, fieldToZap)...)
}

func (l *logger) Error(message string, fields ...Field) {
	l.zapLogger.Error(message, xslices.Map(fields, fieldToZap)...)
}

func (l *logger) With(fields ...Field) Logger {
	zapLogger := l.zapLogger.With(xslices.Map(fields, fieldToZap)...)

	return NewLogger(zapLogger)
}
