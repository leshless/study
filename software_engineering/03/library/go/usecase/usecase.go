package usecase

import "context"

type Usecase[Args any, Res any] interface {
	Execute(ctx context.Context, args Args) (Res, error)
}
