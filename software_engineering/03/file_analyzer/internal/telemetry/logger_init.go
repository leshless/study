package telemetry

import (
	"os"

	"github.com/leshless/golibrary/graceful"

	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
)

const (
	logLevel = zap.DebugLevel
)

func InitLogger(
	gracefulRegistrator graceful.Registrator,
) (*logger, error) {
	zapCore := zapcore.NewCore(
		zapcore.NewJSONEncoder(zap.NewDevelopmentEncoderConfig()),
		zapcore.AddSync(os.Stdout),
		zap.NewAtomicLevelAt(logLevel),
	)

	zapLogger := zap.New(zapCore)

	logger := NewLogger(zapLogger)

	return logger, nil
}
