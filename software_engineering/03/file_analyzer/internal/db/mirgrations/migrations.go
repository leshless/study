package mirgrations

import (
	_ "embed"
)

//go:embed 001.sql
var m001 string

var Migrations = []string{
	m001,
}
