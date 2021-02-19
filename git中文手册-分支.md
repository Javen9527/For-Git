* 分支的原理：Git保存的不是文件的差异，而是文件不同时刻的快照 -> 提交时，保存一个提交对象(commit object)，其包含一个指向快照的指针 + 作者信息 + 指向父对象的指针
* 分支的本质其实是：指向提交对象的可变指针
* 创建分支的过程即：创建一个指针

* master分支（master指针）是默认的分支（即git init时候就创建的指针）
* HEAD分支：即HEAD指针，指向当前分支，是当前分支的别名

* git log --decorate：查看各个分支指向的提交对象
* HEAD分支别名的用途：HEAD分支随着提交操作自动前移

* 分叉：git log --oneline --decorate --graph中，--graph是查看分支分叉情况

* 分支合并：git merge + 分支名 ：始终记住分支是一个指针，合并分支即改变指针，A分支合并B分支，即将A指针移动到B指针上（当前在分支A上即HEAD指向A，在用git merge B）
* 分支合并分为：直接祖先合并 + 分叉三方合并
* 分叉三方合并会产生一次提交，且指向多个父提交
* 合并冲突：合并的分支中有对同一个地方进行不同的修改。产生冲突 -> git status查看冲突 -> 手动解决冲突 -> git add标记冲突解决 -> git commit完成合并 

* 删除分支：git branch -d + 分支名

* git branch 列出所有分支，其中打*号的代表HEAD指向的分支

* git branch -v查看每个分支最后一次提交

* git branch --merged 查看已经合并的分支，对于已经合并的分支，可以通过git branch -d删除
* git branch --no-merged 查看未合并的分支，此时用git branch -d删除会提示删除未合并的修改，也可通过-D强制删除并丢弃更改

* 远程分支 origin是git clone时候默认的远程仓库的名字

* 在git  clone后，会复制所有服务器上的内容（分支）到本地，并在本地将远程分支名添加origin，（这些以origin开头的分支指针无法在本地被更改），同时创建一个本地master分支来作为工作的基础（即可以更改）

* 远程仓库有更新后，本地通过git fetch命令，将本地的origin/master分支更新移动到远程一样的位置

* 跟踪分支：抓取远程分支后（git fetch），本地只有origin开头的不可编辑的分支.

* 跟踪分支的用途：通过git pull会自动抓取服务器上的改变并合并到本地的跟踪分支。

* 克隆一个仓库时，会自动创建一个跟踪分支

* 创建一个远程跟踪分支的命令：git checkout -b <branch> <remote>/<branch>
* 捷径：git checkout --track <remote>/<branch>，会创建一个同名的本地的跟踪分支
* 捷径的捷径：git checkout <branch>：当满足①分支名不存在②刚好只有一个名字与之匹配的远程分支，则会创建一个同名的本地跟踪分支
* 针对本地已有的分支想要跟踪某个远程分支：本地切换到该分支 -> git branch -u（或者--set-upstream-to） <remote>/<branch>

* 查看所有的跟踪分支：git branch -vv

* 本地的跟踪分支落后于远程分支时，通过git fetch获取最新，通过git branch -vv查看落后多少，通过git merge合并  
* 即git pll = git fetch + git merge

* 整合来自不同分支的修改主要的两种方法：merge + rebase

* rebase: 提取一个分支中的修改到另一个分支中。用法：当前所在分子git rebase 另一个分支：即将当前分支相较于他们共同的祖先的修改提取整合到另一个分支上
* rebase的作用是：相比merge 让代码提交更加整洁（串行的提交）可以串改历史
* 如果已经推送到服务器的提交，则不要使用rebase



* git stash

* cherry pick







