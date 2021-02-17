一、本地仓库

   1. git的三个区：工作区 + 暂存区 + 仓库

   2. 通过git add将工作区内容提交到暂存区， 通过git commit将暂存区内容提交到仓库
      · git add
      · git commit

   3. · git diff: 对比工作区和上一次的仓库的内容
      · git diff --cached: 对比暂存区和上一次仓库的内容
      · git diff --head: 对比工作区和暂存区的内容

   4. 添加到暂存区后返回的操作：git reset + filename
      · git reset filename

   5. git log --oneline查看commit历史，使用git checkout + commit编号；再返回当前使用git checkout + master
      理解：有一个head和master指针，使用git checkout + commit编号可以将head指针指向以前的版本，但是master还是指向当前

      要完全回去使用：git reset --hard + commit编号

      在完全回到过去后又想回来，使用git reflog查找到commit编号，再使用git reset --hard commit编号
      · git checkout commit编号/master
      · git reset --hard commit编号
      · git log --oneline
      · git reflog
   
二、分支

   1. 分支
     · 创建分支：git branch 分支名
     · 切换分支：git checkout 分支名
     · git merge

三、远程版本库

   1. 远程版本库


