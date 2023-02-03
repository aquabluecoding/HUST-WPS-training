# git学习目标

## 1. 回答下面的问题

### 问题1 : 根据下面的图片，回答问题

![img](https://cloud-pic.wpsgo.com/elZHYXIvanFnSmRudlladmtQbEdLQURwRmE5cHd6dFJYVk1jdGxsTERtd0t6UjZ3U2hCNW9ZT2F2WHBrbFJweTRZM2FoOWVOOTFhNUowSnA4bHVKSm96bEJocFRNeHBxclNPN2FQN1ZkMk8rRFhQNXMwaVJPcjkxTzFuWG80aDJ2YWdLNjFZcEhuRzNvSlpNcU4wMmtsSXJDQ2gzZTZMWnZRSTU5aXNoMmU5dnZrdzgxdk9MNlM0UFhsSC8yL09CTTVyVWl1U2pPRjBkYlFvS3BvVGFxSmxobWhuRC84a05JWlk4YjJYZksxb25ZM0lhQWErSEdCbGFyTncwMk5PaTYweW8rWmUzOC9LR0ErY05HV2hDYWc9PQ==/attach/object/ERHLCAYA4Y)

- 解释下面概念

- - workspace : 
  - staging area :
  - local repository : 
  - remote repository : 

workspace(工作区)：工作区是本地计算机上的目录，您可以在其中存放特定项目的文件。 您将在此处更改代码并对其进行测试。

staging area(暂存区)：暂存区是一个可以临时存储对代码所做更改但尚未准备好提交到存储库的地方。 这使您可以轻松地查看您的更改并确保您只提交了您想要提交的代码。

local repository(本地存储库)：本地存储库是本地计算机上的一个目录，用于存储项目代码的副本。 它包括项目的所有文件，以及对代码所做的所有更改的历史记录。

remote repository(远程存储库)：远程存储库是存储在远程服务器上而不是本地计算机上的存储库。 它用于与其他开发人员共享代码并存储代码的备份。 当你想与其他人共享你的代码时，你可以将你的更改推送到远程存储库，当你想用其他开发人员所做的最新更改更新你的本地存储库时，你可以从远程存储库中拉取更改。

### 问题2 ： 如何解决 git 冲突?

获取要合并的分支并确保您位于要将更改合并到的分支上。

尝试合并分支。 如果有冲突，Git 会列出它们并在冲突文件中标记它们。

打开冲突文件并查找 Git 留下的标记（例如，<<<<<<<、\=\=\=\=\=\=\=、>>>>>>>）。 这些标记显示了相互冲突的变化。

修改文件，决定要保留哪些更改以及要放弃哪些更改。 可以删除不想保留的分支。

解决冲突后，使用 git add 暂存修改后的文件并提交合并的更改。

将更改推送到远程存储库。

### 问题3 : 出现下面问题的原因与解决方案是什么?

***\*更新代码后显示： unable to unlink old ‘xxx/xxx/xx’ : invalid argument\****

原因：

This error occurs when you are trying to switch branches and Git is unable to delete a file that has been removed from the branch you are switching to. The file may be in use by another program, or it may be locked by the operating system.

解决方案：

To resolve this issue, you can try the following:

1. Close any programs that may be using the file.
2. Try using the `git stash` command to temporarily save your changes, switch branches, and then apply the changes again.
3. If the above steps do not work, you may need to manually delete the file or stop any processes that are using it. You can also try using the `git restore` command to restore the file to a previous version.

If you are still unable to resolve the issue, you may want to try using the `--force` flag with the `git branch` command to forcibly switch branches. However, be aware that this can cause data loss, so use it with caution.

***\*更新代码后显示 :  the following untracked working tree files would be overwritten by checkout\****

原因:

This error occurs when you are trying to switch branches in Git, and you have made local commits or modifications to files that are not present in the branch you are switching to. When you switch branches in Git, it will update the files in your working directory to match the version of the files in the branch you are switching to.

解决方案:

If you have made local commits or modifications to files that are not present in the branch you are switching to, those changes will be overwritten when you switch branches. To resolve this error, you will need to commit or stash your local changes before you can switch branches.

To stash your changes, you can use the `git stash` command. This will temporarily store your local changes and allow you to switch branches. When you are ready to reapply your changes, you can use the `git stash pop` command to apply the stashed changes to your working directory.

Alternatively, you can commit your changes to the current branch before switching to a different branch. This will allow you to switch branches without losing your local changes. To do this, use the `git add` and `git commit` commands to commit your changes to the current branch.

Once you have committed or stashed your local changes, you should be able to switch branches without encountering the "untracked working tree files would be overwritten by checkout" error.

**\*更新代码后显示 : your local changes to the following files would be overwritten by merge…please move or remove them before you merge\***

原因：

This error message occurs when you are trying to merge branches in Git, but there are local changes in your current branch that conflict with the changes in the branch you are trying to merge.

解决方案：

To fix this, you need to either commit or stash your local changes, or you need to discard the local changes by either resetting or discarding the changes in the conflicted files.

Here are the steps you can take to resolve this issue:

1. If you want to keep your local changes, you can commit them to your current branch using `git commit`.
2. If you don't want to commit the changes, but you still want to keep them, you can use `git stash` to temporarily save the changes and apply them back later.
3. If you want to discard the local changes and use the version from the branch you are trying to merge, you can use `git reset --hard` to discard all local changes, or you can use `git checkout -- <file>` to discard the local changes in a specific file.
4. If you want to keep some of the local changes and discard others, you can use `git checkout -- <file>` to discard the changes in a specific file, and then commit the remaining changes using `git commit`.

After you have resolved the conflicts, you can try the merge again.

***\*版本回退git\**** [reset](https://so.csdn.net/so/search?q=reset&spm=1001.2101.3001.7020) ***\*--hard {hash}后提示：fatal: could not parse object “hash id”\****

原因：

The error message "fatal: could not parse object" with a hash value after it usually indicates that the specified object (the commit with the given hash) does not exist in the local repository. This can happen if the commit has been deleted, or if the repository has been damaged in some way.

解决方案：

To fix the problem, you will need to find the correct hash value for the commit that you want to reset to. You can use the `git log` command to find the hashes of the commits in your repository. Once you have the correct hash, you can use the `git reset` command to reset to that commit.

Here is an example of how you can use `git log` and `git reset` to fix the problem:

1. Run `git log` to display the commit history for your repository. This will show you the hashes of the commits, along with the commit messages and other details.
2. Look through the commit history to find the hash of the commit that you want to reset to. Make sure that you have the correct hash, as resetting to the wrong commit can cause problems.
3. Once you have the correct hash, run the `git reset` command with the `--hard` option, followed by the hash of the commit that you want to reset to. For example: `git reset --hard abc123`. This will reset the repository to the specified commit, discarding any changes that have been made since that commit.
4. If the `git reset` command was successful, you should now be able to continue working with your repository as usual.

***\*git push后提示:\****

***\*to https://.git\****

***\*![rejected] localRepo->remoteRepo(fetch first)\****

***\*error: failed to push some refs to ‘https://.git’\****

***\*Updates were rejected because the remote contain work that you do not have locally.\****

原因：

This error can occur when you are trying to push your local commits to a remote repository, but the remote repository has new commits that you do not have in your local repository. This can happen if someone else has pushed to the repository after you last pulled from it.

解决方案：

To fix this, you can try to pull the new commits from the remote repository to your local repository and resolve any conflicts. Once you have done this, you should be able to push your local commits to the remote repository.

To do this, you can run the following command:

```
git pull origin <branch-name>
```

Replace `<branch-name>` with the name of the branch you are working on. This will fetch the latest commits from the remote repository and try to merge them into your local repository. If there are any conflicts, you will need to resolve them before you can push your local commits to the remote repository.

Once you have resolved any conflicts and your local repository is up to date with the remote repository, you should be able to push your local commits to the remote repository using the following command:

```
git push origin <branch-name>
```

Again, replace `<branch-name>` with the name of the branch you are working on. This should push your local commits to the remote repository and update it with your changes.

## 2. 完成下列操作
“<"和”>"之间是替换内容的描述

"["和"]"之间是可选内容的描述

### 1. 克隆仓库

```shell
git clone <url>
```

### 2. 提交修改到暂存区

```shell
git add <filename>/*
```

### 3. 提交修改到远程仓库

```shell
git push <url>
```

### 4. 从远程仓库下载代码

```
git push <远程主机名> <本地分支名>[:<远程分支名>]
```

如果本地分支名与远程分支名相同，则可以省略冒号和之后的内容。

例：以下命令将本地的 master 分支推送到 origin 主机的 master 分支。

```
git push origin master
```

参数 -f 强制推送

### 5. 查看仓库状态

```
git status
```

用于显示工作目录和暂存区的状态。使用此命令能看到那些修改被暂存到了, 哪些没有, 哪些文件没有被Git tracked到。`git status`不显示已经`commit`到项目历史中去的信息。看项目历史的信息要使用`git log`.

### 6. 比较文件的不同,即暂存区与工作区的差别

`git diff`命令用于显示提交和工作树等之间的更改。此命令比较的是工作目录中当前文件和暂存区域快照之间的差异,也就是修改之后还没有暂存起来的变化内容。

```
git diff <file> # 比较当前文件和暂存区文件差异

git diff <id1><id1><id2> # 比较两次提交之间的差异

git diff <branch1> <branch2> # 在两个分支之间比较

git diff --staged [file] # 比较暂存区和版本库差异
git diff --cached [file] # 比较暂存区和版本库差异

git diff --stat # 仅仅比较统计信息
```

更多使用方法参考https://www.yiibai.com/git/git_diff.html

### 7. 创建分支/切换分支/查看分支列表

本地创建分支：

```
git branch <分支名>
```

本地新建分支并切换到该分支

```
git checkout -b <分支名>
```

新建本地分支与远程分支相关联

```
git checkout -b <本地分支名> <远程主机名>/<远程分支名> 
```

切换到已有分支dev：

```
git checkout dev
```

查看分支列表：

```
git branch
```

### 8. 上传代码到分支上

```
git commit [-m message]
```

### 9. 合并分支到主分支

将某分支合并到当前分支：

```
git merge <分支名>
```

### 10. 删除分支

本地删除分支：

```
git branch -D/d <分支名>
```

### 11. 回退到某个版本

首先，Git必须知道当前版本是哪个版本，在Git中，用`HEAD`表示当前版本，也就是最新的提交，上一个版本就是`HEAD^`，上上一个版本就是`HEAD^^`，当然往上100个版本写100个`^`比较容易数不过来，所以写成`HEAD~100`。

先用`git log`查看历史修改信息，得到commit id

```
git reset [--soft | --mixed | --hard] [版本]
```

"[版本]"既可以使用`HEAD`推导式，也可以使用`git log`中得到的版本号（版本号没必要写全，前几位就可以了）

**--mixed** 为默认，可以不用带该参数，用于重置暂存区的文件与上一次的提交(commit)保持一致，工作区文件内容保持不变。

**--soft** 参数用于回退到某个版本。

**--hard** 参数撤销工作区中所有未提交的修改内容，将暂存区与工作区都回到上一次版本，并删除之前的所有信息提交。

注意：`--hard`会删除回退点之前的所有信息。

想要恢复这些被“删除”的信息，可以使用commit id回到那个版本

想要查看commit id，可以使用`git reflog`查看命令的历史记录
