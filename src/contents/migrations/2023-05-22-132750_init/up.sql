/**
 * SPDX-FileCopyrightText: (C) 2020 Carl Schwan <carl@carlschwan.eu>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

CREATE TABLE IF NOT EXISTS SavedColorModel (
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    Name TEXT NOT NULL,
    ForegroundColor BLOB NOT NULL,
    BackgroundColor BLOB NOT NULL
)
