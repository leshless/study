CREATE TABLE IF NOT EXISTS submissions (
    id TEXT PRIMARY KEY,
    work_name TEXT NOT NULL,
    student_name TEXT NOT NULL,
    object_id TEXT NOT NULL,
    created_time TIMESTAMPTZ NOT NULL
);