/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#ifndef VFS_H
#define VFS_H

#include "include/types/types.h"

struct fs_node;

/* These typedefs define the type of callbacks -
 * called when read/write/open/close
 */
typedef uint32 (*read_type_t)(struct fs_node *, uint32, uint32, uint8 *);
typedef uint32 (*write_type_t)(struct fs_node *, uint32, uint32, uint8 *);
typedef void   (*open_type_t)(struct fs_node *);
typedef void   (*close_type_t)(struct fs_node *);
typedef struct dirent * (*readdir_type_t)(struct fs_node *, uint32);
typedef struct fs_node * (*finddir_type_t)(struct fs_node *, char *name);

/* One of these is returned by the readdir call, according to POSIX. */
struct dirent
{
    char name[128];     /* Filename */
    uint32 ino;         /* Inode number. Required by POSIX. */
};

#define FS_FILE         0x01
#define FS_DIRECTORY    0x02
#define FS_CHARDEVICE   0x03
#define FS_BLOCKDEVICE  0x04
#define FS_PIPE         0x05
#define FS_SYMLINK      0x06
#define FS_MOUNTPOINT   0x08 /* This is given value 8 and not 7 to be able to be OR'd with FS_DIRECTORY */

typedef struct fs_node
{
    char name[128];         /* The filename. */
    uint32 mask;            /* The permissions mask. */
    uint32 uid;             /* The owning user. */
    uint32 gid;             /* The owning group. */
    uint32 flags;           /* Includes the node type. See #defines above */
    uint32 inode;           /* This is device-specific - provides a way for a filesystem to identify files. */
    uint32 length;          /* Size of the file, in bytes. */
    uint32 impl;            /* An implementation defined number. */
    read_type_t     read;
    write_type_t    write;
    open_type_t     open;
    close_type_t    close;
    readdir_type_t  readdir;
    finddir_type_t  finddir;
    struct fs_node *ptr;    /* Used by mountpoints and symlinks */
} fs_node_t;

extern fs_node_t  *fs_root;     /* The root of the filesystem */

struct vfs_dir;

typedef struct __attribute__((packed)) vfs_file  {
    char *name;
    char *content;
    uint32 size;
    struct vfs_file *sibling;
    struct vfs_dir* parent;
} vfs_file_t;

typedef struct __attribute__((packed)) vfs_dir {
    char *name;
    vfs_file_t *first_file;
    struct vfs_dir *first_dir;
    struct vfs_dir *sibling;
    struct vfs_dir* parent;
} vfs_dir_t;

/* Standard read/write/open/close functions. Note that these are all suffixed with
 * _fs to distinguish them from the read/write/open/close which deal with the file
 * descriptors, not file nodes.
 */
uint32 read_fs  (fs_node_t *node, uint32 offset, uint32 size, uint8 *buffer);
uint32 write_fs (fs_node_t *node, uint32 offset, uint32 size, uint8 *buffer);
void   open_fs  (fs_node_t *node, uint8 read, uint8 write);
void   close_fs (fs_node_t *node);
struct dirent *readdir_fs (fs_node_t *node, uint32 index);
fs_node_t *finddir_fs (fs_node_t *node, char *name);
vfs_file_t *vfs_make_file(char *name);
vfs_dir_t *vfs_make_dir(char *name);
void vfs_add_file(vfs_file_t *add, vfs_dir_t *dir);
void vfs_add_dir(vfs_dir_t *add, vfs_dir_t *dir);

#endif


