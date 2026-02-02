package telemetry

import (
	"time"

	"go.uber.org/zap"
)

type Field struct {
	value any
	key   string
}

func fieldToZap(f Field) zap.Field {
	switch typedValue := f.value.(type) {
	case string:
		return zap.String(f.key, typedValue)
	case int:
		return zap.Int(f.key, typedValue)
	case uint:
		return zap.Uint(f.key, typedValue)
	case uint64:
		return zap.Uint64(f.key, typedValue)
	case time.Time:
		return zap.Time(f.key, typedValue)
	case time.Duration:
		return zap.Duration(f.key, typedValue)
	case error:
		return zap.Error(typedValue)
	}

	return zap.Any(f.key, f.value)
}

func String(key string, value string) Field {
	return Field{
		key:   key,
		value: value,
	}
}

func Int(key string, value int) Field {
	return Field{
		key:   key,
		value: value,
	}
}

func Uint(key string, value uint) Field {
	return Field{
		key:   key,
		value: value,
	}
}

func Uint64(key string, value uint64) Field {
	return Field{
		key:   key,
		value: value,
	}
}

func Time(key string, value time.Time) Field {
	return Field{
		key:   key,
		value: value,
	}
}

func Duration(key string, value time.Duration) Field {
	return Field{
		key:   key,
		value: value,
	}
}

func Error(value error) Field {
	return Field{
		value: value,
	}
}
