#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[20];
    float salary;
} Employee;

int main() {
    int fd;
    Employee emp1 = {1, "Alice", 50000.0};
    Employee emp2 = {2, "Bob", 60000.0};
    Employee empRead;

    // 1. Create and Write records
    fd = open("employees.dat", O_CREAT | O_RDWR | O_TRUNC, 0600);
    if (fd < 0) return 1;
    
    write(fd, &emp1, sizeof(Employee));
    write(fd, &emp2, sizeof(Employee));

    // 2. Update specific record (Bob's salary) without rewriting the file
    emp2.salary = 65000.0;
    lseek(fd, sizeof(Employee), SEEK_SET);
    write(fd, &emp2, sizeof(Employee));

    // 3. Retrieve record from a specific location efficiently
    lseek(fd, 0, SEEK_SET);
    read(fd, &empRead, sizeof(Employee));
    printf("Read ID: %d, Name: %s, Salary: %.2f\n", empRead.id, empRead.name, empRead.salary);
    
    // Read updated Bob
    read(fd, &empRead, sizeof(Employee));
    printf("Read ID: %d, Name: %s, Salary: %.2f\n", empRead.id, empRead.name, empRead.salary);

    close(fd);
    return 0;
}