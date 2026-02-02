CREATE TABLE IF NOT EXISTS reports (
    id TEXT PRIMARY KEY,
    work_name TEXT NOT NULL,
    submission_id TEXT NOT NULL,
    originality_percent DOUBLE PRECISION NOT NULL,
    similar_submission_ids JSON NOT NULL,
    creation_time TIMESTAMPTZ NOT NULL
);