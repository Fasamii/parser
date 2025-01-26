#pragma once

int treeAddLevels(ExecTree *parent, int size);
int treeAppendLevel(ExecTree *parent);
int treePrependLevel(ExecTree *parent);
int treeAppendLevelWith(ExecTree *parent, ExecTree *child);
int treePrependLevelWith(ExecTree *parent, ExecTree *child);
int treeCopyToContent(ExecTree *treeNode, char *contenr);
int treeNodeRemoveContent(ExecTree *treeNode);
int treeRemoveNodeAndChilds(ExecTree *treeNode);
char *treeGetContentPointer(ExecTree *treeNode);
char *treeCopyContentToPointer(ExecTree *treeNode);
