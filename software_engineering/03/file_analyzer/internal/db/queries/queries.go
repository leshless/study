package queries

import _ "embed"

//go:embed insert_report.sql
var InsertReport string

//go:embed select_reports.sql
var SelectReports string
