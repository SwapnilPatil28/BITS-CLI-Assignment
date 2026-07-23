mkdir -p submissions backup

exec 2> error_log.txt

# Create some test files (simulating submissions)
echo "Code A" > submissions/student1.txt
echo "Code B" > submissions/student2.txt
echo "Code A" > submissions/student3.txt # Duplicate of student1

total_files=$(ls submissions | wc -l)
unique_count=0
duplicate_count=0

# Array to keep track of seen hashes
declare -A seen_hashes

for file in submissions/*; do
    if [ -f "$file" ]; then
        hash=$(md5sum "$file" | awk '{print $1}')
        
        if [[ -n "${seen_hashes[$hash]}" ]]; then
            ((duplicate_count++))
            echo "Duplicate found: $file"
        else
            seen_hashes[$hash]=1
            cp "$file" backup/
            ((unique_count++))
        fi
    fi
done

# Generate report
echo "--- Processing Report ---" > report.txt
echo "Total Files Processed: $total_files" >> report.txt
echo "Unique Files Backed Up: $unique_count" >> report.txt
echo "Duplicate Files Found: $duplicate_count" >> report.txt

cat report.txt