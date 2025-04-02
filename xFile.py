import os
from shutil import copyfile

source_dir = 'D:/CAD/'  # 仓库源路径
paster_dir = 'D:/CAD/MantiSoftX'  # 新路径 或 要还原的路径


class HandleFile:
    def __init__(self, copy_dir, paster_dir, ignore_dir):
        self.copy_dir = copy_dir
        self.paster_dir = paster_dir
        self.ignore_dir = ignore_dir
        self.add_suffix = '_aprilxx'

    def __is_txt_file(self, fileName: str):
        try:
            with open(fileName, 'r', encoding='utf-8') as file:
                for line in file:
                    break
            return True
        except UnicodeDecodeError:
            return False
        except Exception as e:
            return False

    def copy_files(self):
        print(f"\n开始复制文件，源路径为：{self.copy_dir}，目标路径为：{self.paster_dir}")
        countIndex = 0
        parentPath = '@'
        pathLen = len(self.copy_dir)
        errorList = []

        for rootDir, dirName, fileNames in os.walk(self.copy_dir):
            strFind = '\\'
            rootDir = rootDir.replace('\\', '/')
            nPos = rootDir.rfind('/')
            curDir = rootDir[nPos + len(strFind):]
            if curDir in self.ignore_dir:
                print(f"跳过忽略的文件夹：{curDir}")
                parentPath = rootDir
                continue

            subPos = rootDir.find(parentPath)
            if subPos >= 0:
                continue

            parentPath = '@'

            mkDir = self.paster_dir + '/' + rootDir[pathLen:]
            if not os.path.exists(mkDir):
                try:
                    os.mkdir(mkDir)
                    print(f"创建目录：{mkDir}")
                except Exception as e:
                    print(f"创建目录失败：{mkDir}，错误信息：{e}")
                    continue

            for strFileName in fileNames:
                countIndex += 1

                originFile = os.path.join(rootDir, strFileName)
                fInfo = os.path.splitext(originFile)

                fileSuffix = fInfo[-1].lower()

                if self.__is_txt_file(originFile) or fileSuffix.lower() == ".idx":
                    try:
                        binOpen = open(originFile, 'rb')
                        binCont = binOpen.read()
                        binOpen.close()

                        newFileName = mkDir + '/' + strFileName + self.add_suffix
                        newFile = open(newFileName, 'wb')
                        e = newFile.write(binCont)
                        newFile.close()
                        print(f"复制并添加后缀：{originFile} -> {newFileName}")
                    except Exception as e:
                        print(f"复制文件失败：{originFile}，错误信息：{e}")
                        errorList.append(f"\n!!!!!!!!!!!! xError {fileSuffix} -> {originFile} to {newFileName}\n")
                    finally:
                        if len(fileSuffix) < 1:
                            fileSuffix = "        "

                else:
                    newFileName = mkDir + '/' + strFileName
                    try:
                        dst = copyfile(originFile, newFileName)
                        print(f"直接复制文件：{originFile} -> {newFileName}")
                    except Exception as e:
                        print(f"复制文件失败：{originFile}，错误信息：{e}")
                        errorList.append(f"\n!!!!!!!!!!!! Copy xError {fileSuffix} -> {originFile} to {newFileName}\n")

        print(f"复制完成，共处理 {countIndex} 个文件")
        if errorList:
            print("\n发生错误的文件列表：")
            for e in errorList:
                print(e)

    def rnameSuffix(self):
        print(f"\n开始还原文件，路径为：{self.paster_dir}")
        removeLen = len(self.add_suffix)
        countIndex = 0
        errorList = []

        for root, dirname, filename in os.walk(self.paster_dir):
            for f in filename:
                strSuffix = f[-removeLen:]

                if strSuffix == self.add_suffix:
                    fileName = os.path.join(root, f)
                    newName = fileName[:-removeLen]
                    try:
                        if not os.path.exists(newName):
                            os.rename(fileName, newName)
                            print(f"还原文件名：{fileName} -> {newName}")
                        else:
                            os.remove(fileName)
                            print(f"目标文件已存在，删除文件：{fileName}")
                    except Exception as e:
                        print(f"还原文件失败：{fileName}，错误信息：{e}")
                        errorList.append(f"\n!!!!!!!!!!!! Rename xError {fileName} to {newName}\n")
                    finally:
                        countIndex += 1

        print(f"还原完成，共处理 {countIndex} 个文件")
        if errorList:
            print("\n发生错误的文件列表：")
            for e in errorList:
                print(e)


if __name__ == '__main__':
    print('-------------------------')
    print('----------Begin----------')

    chooseRep = input("\n选择要操作的类型:\n1:复制\n2:还原\n\n")
    if chooseRep == "1":
        opt_copy = True
    elif chooseRep == "2":
        opt_copy = False
    else:
        print("无效的选择！")
        raise ValueError("请选择有效的选项: 1 或 2")

    ignore_dir = ['.vs', '.vscode', '.ide', 'build', 'CMake-build', 'Depends', 'x64', 'x86', 'RDNet']

    if opt_copy:
        print('\n\n\n\n\n\n')

        repName = None
        chooseRep = input(f"\n操作 {source_dir} 中的仓库\n选择要操作的仓库名称:\n1: Upstream\n2: MantiSoft\n3: 自定义目录\n\n")

        if chooseRep == "1":
            repName = 'Upstream'
            copy_dir = f'{source_dir}/{repName}/'
            print(f"选择的仓库为：{repName}")
        elif chooseRep == "2":
            repName = 'MantiSoft'
            copy_dir = f'{source_dir}/{repName}/'
            print(f"选择的仓库为：{repName}")
        elif chooseRep == "3":
            custom_dir = input("请输入自定义目录名称, 如果为空或输入'.'，则使用当前路径: ").strip()
            if not custom_dir or custom_dir == '.':
                copy_dir = os.getcwd()  # 如果为空或为'.'，则使用当前路径
                paster_dir = copy_dir + '_X'  # 直接在当前路径后添加_X后缀
                print(f"未输入路径或输入为'.'，使用当前路径：{copy_dir}")
                print(f"目标路径为：{paster_dir}")
            else:
                copy_dir = custom_dir
                paster_dir = custom_dir + '_X'  # 在指定路径后添加_X后缀
                print(f"指定的源路径为：{copy_dir}，目标路径为：{paster_dir}")

        else:
            print("无效的选择！")
            raise ValueError("请选择有效的选项: 1, 2 或 3")

        if not os.path.exists(copy_dir):
            print(f'路径不存在：{copy_dir}')
            raise OSError(f"源路径不存在: {copy_dir}")

        print(f'......开始复制文件: {copy_dir} -> {paster_dir}')

        handle_obj = HandleFile(copy_dir, paster_dir, ignore_dir)
        handle_obj.copy_files()

        if not os.path.exists(paster_dir):
            print(f'路径不存在：{paster_dir}')
            raise OSError(f"目标路径不存在: {paster_dir}")

    else:
        print('xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n')
        
        # 添加还原时的自定义目录选项
        chooseRep = input(f"\n选择要还原的目录:\n1: 默认路径 ({paster_dir})\n2: 自定义目录\n\n")
        if chooseRep == "1":
            restore_dir = paster_dir
        elif chooseRep == "2":
            custom_dir = input("请输入要还原的目录路径: ").strip()
            if not custom_dir:
                print("未输入路径，使用默认路径")
                restore_dir = paster_dir
            else:
                restore_dir = custom_dir
        else:
            print("无效的选择，使用默认路径")
            restore_dir = paster_dir
        
        print(f'......开始还原文件: {restore_dir}')

        handle_obj = HandleFile(restore_dir, restore_dir, ignore_dir)
        handle_obj.rnameSuffix()

    print('\n......The End......')