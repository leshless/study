package queries

import _ "embed"

//go:embed insert_submission.sql
var InsertSubmission string

//go:embed select_submission.sql
var SelectSubmission string

//go:embed select_work_submissions.sql
var SelectWorkSubmissions string
