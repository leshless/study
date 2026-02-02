package main

import "swe3/file_storer/internal/app"

func main() {
	app, err := app.Init()
	if err != nil {
		panic(err)
	}

	if err := app.Run(); err != nil {
		panic(err)
	}
}
