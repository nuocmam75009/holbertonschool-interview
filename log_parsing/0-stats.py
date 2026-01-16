#!/usr/bin/python3
"""
Log parsing script that reads stdin line by line and computes metrics.
"""

import sys
import re


def parse_log_line(line):
    """
    Parse a log line and extract status code and file size.

    Format: <IP Address> - [<date>] "GET /projects/260 HTTP/1.1" <status code> <file size>

    Returns:
        tuple: (status_code, file_size) or (None, None) if line doesn't match format
    """
    pattern = r'^\d+\.\d+\.\d+\.\d+ - \[.*?\] "GET /projects/260 HTTP/1\.1" (\d+) (\d+)$'
    match = re.match(pattern, line.strip())

    if match:
        status_code = int(match.group(1))
        file_size = int(match.group(2))
        return status_code, file_size
    return None, None


def print_stats(total_size, status_counts):
    """
    Print statistics: total file size and status code counts.

    Args:
        total_size: Total file size accumulated
        status_counts: Dictionary mapping status codes to their counts
    """
    print(f"File size: {total_size}")

    # Print status codes in ascending order
    valid_status_codes = [200, 301, 400, 401, 403, 404, 405, 500]
    for status_code in valid_status_codes:
        if status_code in status_counts and status_counts[status_code] > 0:
            print(f"{status_code}: {status_counts[status_code]}")


def main():
    """Main function to process log lines and print statistics."""
    total_size = 0
    status_counts = {}
    line_count = 0

    try:
        for line in sys.stdin:
            status_code, file_size = parse_log_line(line)

            if status_code is not None and file_size is not None:
                # Update total file size
                total_size += file_size

                # Update status code count
                if status_code in status_counts:
                    status_counts[status_code] += 1
                else:
                    status_counts[status_code] = 1

                line_count += 1

                # Print statistics after every 10 lines
                if line_count % 10 == 0:
                    print_stats(total_size, status_counts)

    except KeyboardInterrupt:
        # Print statistics on keyboard interruption
        print_stats(total_size, status_counts)
        raise


if __name__ == "__main__":
    main()

