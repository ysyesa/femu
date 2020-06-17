#include "fs.h"

#include "hw/block/block.h"
#include "hw/pci/msix.h"
#include "hw/pci/msi.h"
#include "../nvme.h"

struct fs_inode *fs_get_inode_of_fd(struct fs_inode_table *inode_table, int fd) {
//    for (int i = 1; i <= inode_table->num_entries; i++) {
//        struct fs_inode *inode = &inode_table->inodes[i];
//        if (inode->number == fd) {
//            return inode;
//        }
//    }
}

uint64_t fs_get_fd_of_file(struct fs_inode_table *inode_table, char *filename) {
//    for (int i = 1; i <= inode_table->max_entries; i++) {
//        struct fs_inode *inode = &inode_table->inodes[i];
//        if (inode->is_used && strcmp(filename, inode->filename) == 0) {
//            return inode->number;
//        }
//    }
//    return FS_FILENAME_NOT_FOUND;
}

uint64_t fs_get_unused_inode_index(struct fs_inode_table *inode_table) {
//    for (int i = 1; i <= inode_table->max_entries; i++) {
//        if (!inode_table->inodes[i].is_used) {
//            return i;
//        }
//    }
//    return FS_NO_INODE_AVAILABLE;
}

void fs_init_inode(FemuCtrl *n, uint64_t number) {
    struct fs_inode inode = n->inode_table->inodes[number];
    inode.type = FS_INODE_FILE;
    inode.filename = "";
    inode.number = number;
    inode.address = (number - 1) * n->metadata.max_file_size;
    inode.length = 0;
    inode.is_used = false;
}

uint64_t fs_open_file(struct fs_inode_table *inode_table, char *filename) {
//    uint64_t fd = fs_get_fd_of_file(inode_table, filename);
//    if (fd != FS_FILENAME_NOT_FOUND)
//        return fd;
//
//    uint64_t unused_inode_index = fs_get_unused_inode_index(inode_table);
//    if (unused_inode_index == FS_NO_INODE_AVAILABLE) {
//        printf("YESA LOG: No inode available\n");
//        abort();
//    }
//    struct fs_inode *inode = &inode_table->inodes[unused_inode_index];
//    inode->filename = filename;
//    inode->is_used = true;
//    inode_table->num_entries++;
//    return inode->number;
}

void fs_close_file(struct fs_inode_table *inode_table, uint64_t fd) {
//    struct fs_inode *inode = fs_get_inode_of_fd(inode_table, fd);
//    if (!inode->is_used) {
//        printf("YESA LOG: fd has not been used\n");
//        abort();
//    }
//    inode->is_used = false;
}

void fs_init_metadata(FemuCtrl *n) {
    if (n->max_file_total == 0) {
        if (n->max_file_size == 0) {
            n->max_file_total = 4;
            n->max_file_size = n->mbe.size / n->max_file_total;
        } else {
            n->max_file_total = n->mbe.size / n->max_file_size;
        }
    } else {
        n->max_file_size = n->mbe.size / n->max_file_total;
    }
    n->metadata.max_file_total = n->max_file_total;
    n->metadata.max_file_size = n->max_file_size;
}

void fs_init_inode_table(FemuCtrl *n) {
    n->inode_table = malloc(sizeof(struct fs_inode_table));
    n->inode_table->num_entries = 0;
    n->inode_table->inodes = malloc(sizeof(struct fs_inode) * (n->metadata.max_file_total + 1 ));
    if (n->inode_table->inodes == NULL) {
        printf("YESA LOG: Inode table allocation failed\n");
        abort();
    } else {
        printf("YESA LOG: Inode table allocation success.\n");
        printf("YESA LOG: Max file total in FS = %" PRIu64 "\n", n->metadata.max_file_total);
        printf("YESA LOG: Max file size in FS  = %" PRIu64 "\n", n->metadata.max_file_size);
    }

    for (int i = 1; i <= n->metadata.max_file_total; i++) {
        fs_init_inode(n, i);
    }
}

void fs_init(FemuCtrl *n) {
    fs_init_metadata(n);
    fs_init_inode_table(n);
}

uint64_t nvme_fs_open(FemuCtrl *n, NvmeNamespace *ns, NvmeCmd *cmd, int index_poller) {
//    NvmeFsCmd *fs_cmd = (NvmeFsCmd *)cmd;
//
//    uint32_t nlb  = le16_to_cpu(fs_cmd->nlb) + 1;
//    uint64_t slba = le64_to_cpu(fs_cmd->slba);
//    uint64_t prp1 = le64_to_cpu(fs_cmd->prp1);
//    const uint8_t lba_index = NVME_ID_NS_FLBAS_INDEX(ns->id_ns.flbas);
//    const uint8_t data_shift = ns->id_ns.lbaf[lba_index].ds;
//    uint64_t data_size = (uint64_t)nlb << data_shift;
//    uint64_t data_offset = slba << data_shift;
//
//    address_space_rw(&address_space_memory, prp1, MEMTXATTRS_UNSPECIFIED, n->inode_table->filename_buf[index_poller], n->page_size, false);
//    fs_open_file(n->inode_table, n->inode_table->filename_buf);

    return NVME_SUCCESS;
}

uint64_t nvme_fs_close(FemuCtrl *n, NvmeNamespace *ns, NvmeCmd *cmd) {
//    NvmeFsCmd *fs_cmd = (NvmeFsCmd *)cmd;
    return NVME_SUCCESS;
}

uint64_t nvme_fs_read(FemuCtrl *n, NvmeNamespace *ns, NvmeCmd *cmd, int index_poller, int sq_id) {
//    NvmeFsCmd *fs_cmd = (NvmeFsCmd *)cmd;
//
//    uint64_t prp1 = le64_to_cpu(fs_cmd->prp1);
//
//    address_space_rw(&address_space_memory, prp1, MEMTXATTRS_UNSPECIFIED, n->inode_table->test_buffer[index_poller], n->page_size, true);

    return NVME_SUCCESS;
}

uint64_t nvme_fs_write(FemuCtrl *n, NvmeNamespace *ns, NvmeCmd *cmd, int index_poller, int sq_id) {
//    NvmeFsCmd *fs_cmd = (NvmeFsCmd *)cmd;
//
//    uint64_t prp1 = le64_to_cpu(fs_cmd->prp1);
//
//    address_space_rw(&address_space_memory, prp1, MEMTXATTRS_UNSPECIFIED, n->inode_table->test_buffer[index_poller], n->page_size, false);

    return NVME_SUCCESS;
}

uint64_t nvme_fs_lseek(FemuCtrl *n, NvmeNamespace *ns, NvmeCmd *cmd) {
//    NvmeFsCmd *fs_cmd = (NvmeFsCmd *)cmd;
    return NVME_SUCCESS;
}
