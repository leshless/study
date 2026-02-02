package telemetry

import (
	"os"

	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
)

const (
	logLevel = zap.DebugLevel
)

func InitLogger() (*logger, error) {
	zapCore := zapcore.NewCore(
		zapcore.NewJSONEncoder(zap.NewDevelopmentEncoderConfig()),
		zapcore.AddSync(os.Stdout),
		zap.NewAtomicLevelAt(logLevel),
	)

	zapLogger := zap.New(zapCore)

	logger := NewLogger(zapLogger)

	return logger, nil
}
