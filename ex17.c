#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Database {
  struct Address rows[MAX_ROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void die(const char *message)
{
  if (errno) {
    perror(message);
  } else {
    printf("Error: %s", message);
  }

  exit(1);
}

void Address_print(struct Address *address)
{
  printf("%d %s %s\n", address->id, address->name, address->email);
}

/*
  Will load previous db info into conn->db
 */
void Database_load(struct Connection *conn)
{
  /*
   Read copies contents in (connection.db, size of database, how many items reading,
   and finally the stream(file) to read from.
   */
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  // return value the number of objects read
  if (rc != 1) {
    die("Failed to load db");
  }
}

struct Connection *Database_open(char *filename, char mode)
{
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) {
    die("Mememory Error");
  }
  conn->db = malloc(sizeof(struct Database));
  if (!conn->db) {
    die("Mememory Error");
  }

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }

  if (!conn->file) {
    die("Failed to open file");
  }
  return conn;
}

void Database_close(struct Connection *conn)
{
  if (conn) {
    if (conn->file) {
      fclose(conn->file);
    }
    if (conn->db) {
      free(conn->db);
    }
    free(conn);
  }
}

void Database_write(struct Connection *conn)
{
  rewind(conn->file); // Go to beginning of the file

  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file); // Will write to a buffer
  if (rc != 1) {
    die("Failed to write to db");
  }

  rc = fflush(conn->file); // forces the buffer to write
  // returns -1 on error
  if (rc == -1) {
    die("Can not flush the db");
  }
}

void Database_create(struct Connection *conn) {
  int i = 0;
  for (i = 0; i < MAX_ROWS; i++) {
    // This is done on the stack
    struct Address address = { .id = i, .set = 0 };
    // values of this pointer is now the address data
    // struct assignment, no need to do memcpy on structs only for arrays and
    // strings i guess
    conn->db->rows[i] = address;
  }
}

void Database_set(struct Connection *conn, int id, char *name, char *email)
{
  struct Address *address = &conn->db->rows[id];
  if (address->set == 1) {
    die("Already set, delete first.");
  }
  // Change the contents of the row in the db if not set
  address->set = 1;
  char *res = strncpy(address->name, name, MAX_DATA);
  if (!res) {
    die("String Copy Failed for name");
  }
  res = strncpy(address->email, email, MAX_DATA);
  if (!res) {
    die("String Copy Failed for email");
  }
}

void Database_get(struct Connection *conn, int id)
{
  // Here we use & because rows[id] returns the contents and we need the
  // full address struct
  struct Address *address = &conn->db->rows[id];
  if (address->set) {
    Address_print(address);
  } else {
    die("Address ID is not set");
  }
}

void Database_delete(struct Connection *conn, int id)
{
  struct Address address = {.id = id, .set = 0};
  conn->db->rows[id] = address;
}

void Database_list(struct Connection *conn)
{
  // Here we dont use & because were already getting the pointer back and not
  // using and [] or (*[val]) to get any value *(ptr + id)
  // (*struct).[field] uses other places --- NOTES IS not important
  struct Database *db = conn->db;
  int i = 0;
  for (i = 0; i < MAX_ROWS; i++) {
    // struct Address address = db->rows[i]; // This would copy is onto stack
    struct Address *cur = &db->rows[i];
    if (cur->set) {
      Address_print(cur);
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 3) {
    die("USAGE: ex17 <dbfile> <action> [action params]\n");
  }
  char *filename = argv[1];
  char action = argv[2][0]; // first character of second arg

  int id = 0;
  if (argc > 3) {
    id = atoi(argv[3]);
  }
  if (id > MAX_ROWS) {
    die("There are not that many records");
  }
  struct Connection *conn = Database_open(filename, action);
  switch (action) {
    // Creates an empty db
    case 'c':
      Database_create(conn);
      Database_write(conn);
      break;
    case 's':
      if (argc != 6) {
        die("Need id, name, email");
      }
      Database_set(conn, id, argv[4], argv[5]); // char* arg[] already returns pointer
      Database_write(conn);
      break;
    case 'g':
      if (argc != 4) {
        die("Need id");
      }
      Database_get(conn, id);
      break;
    case 'd':
      if (argc != 4) {
        die("Need id");
      }
      Database_delete(conn, id);
      Database_write(conn);
      break;
    case 'l':
      Database_list(conn);
      break;
    default:
      printf("Command Not Found: l=list, d=delete, g=get, c=create, s=set\n");
  }
  Database_close(conn);
  return 0;
}
