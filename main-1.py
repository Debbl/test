import re
import sys


# 输出菜单
def menu():
    print('''
    ------------学生信息管理系统----------
    |                                 |
    |============= *功能菜单* ==========
    |
    |     1 录入学生信息
    |     2 查找学生信息
    |     3 删除学生信息
    |     4 修改学生信息
    |     5 成绩排序
    |     6 统计成绩
    |     7 显示所有学生信息
    |     0 退出系统
    |===============================|
    |     说明：通过数字选择菜单        |
    |-------------------------------|
    ''')


# 录入学生成绩
def insert():
    while True:
        ID = input("请输入ID（如1001）：")
        if not ID:  # ID为空，跳出循环
            break
        name = input("请输入名字：")
        if not name:  # 名字为空，跳出循环
            break
        math = int(input("请输入数学成绩："))
        python = int(input("请输入Python成绩："))
        sports = int(input("请输入体育成绩："))
        # 将输入的学生信息保存到字典
        student = {"ID": ID, "name": name, "math": math, "python": python, "sports": sports}
        students_dict[ID] = student  # 将学生字典添加到列表中
        inputMark = input("是否继续添加? (y/n) :")
        if inputMark == "y":  # 继续添加
            continue
        else:  # 不继续添加
            break
    show()
    print("学生信息录入完毕！！！")


# 显示学生成绩
def show():
    students_list = []
    for student in students_dict:
        students_list.append(students_dict[student])
    print("ID\t\t名字\t数学成绩\tPython成绩\t体育成绩\n")
    for student in students_list:
        print(student['ID'] + "\t" + student['name'] + "\t\t" + str(student['math']) + "\t\t" + str(student['python']) + "\t\t" + str(student["sports"]))


# 删除学生成绩
def delete():
    while True:
        student_id = input("请输入要删除学生的ID：")
        if student_id in students_dict:
            del students_dict[student_id]
            print("ID为 " + student_id + " 的学生信息已经被删除...\n")
            show()
        else:
            show()
        input_mark = input("是否继续删除？ (y/n) :")
        if input_mark == "y":
            continue
        else:
            break


# 修改学生成绩
def modify():
    while True:
        show()
        student_id = input("请输入要修改学生的ID：")
        if student_id in students_dict:
            print("找到了这名学生，可以修改她的信息")

            name = input("请输入名字：")
            if not name:  # 名字为空，跳出循环
                break

            math = int(input("请输入数学成绩："))
            python = int(input("请输入Python成绩："))
            sports = int(input("请输入体育成绩："))
            student = {"name": name, "math": math, "python": python, "sports": sports}
            students_dict[student_id].update(student)
        else:
            show()
        input_mark = input("是否继续修改其他学生信息？ (y/n) :")
        if input_mark == "y":
            continue
        else:
            print("学生信息修改完成！")
            break


# 查询学生成绩
def search():
    while True:
        search_type = input("按ID输入请输入1；按姓名查输入2：")
        if search_type == "1":
            student_id = input("请输入学生ID：")
            print("ID\t\t名字\t数学成绩\tPython成绩\t体育成绩\n")
            search_student_id = students_dict[student_id]
            print(search_student_id['ID'] + "\t" + search_student_id['name'] + "\t\t" + str(search_student_id['math']) + "\t\t" + str(
                    search_student_id['python']) + "\t\t" + str(search_student_id["sports"]))
        elif search_type == "2":
            student_name = input("请输入学生姓名")
            print("ID\t\t名字\t数学成绩\tPython成绩\t体育成绩\n")
            for student_id in students_dict:
                if student_name == students_dict[student_id]['name']:
                    search_student_id = students_dict[student_id]
                    print(search_student_id['ID'] + "\t" + search_student_id['name'] + "\t\t" + str(
                        search_student_id['math']) + "\t\t" + str(
                        search_student_id['python']) + "\t\t" + str(search_student_id["sports"]))
        else:
            print("输入错误！！！")
        input_mark = input("是否继续查询？ (y/n) :")
        if input_mark == "y":
            continue
        else:
            break


# 学生成绩排序函数
def sort():
    while True:
        show()
        asc_or_desc = int(input("请选择（0升序；1降序）："))
        sort_type = input("请选择排序方式（1按数学成绩排序；2按Python成绩排序；3按体育成绩排序；0按总成绩排序）")
        students_new = []
        for student in students_dict:
            students_new.append(students_dict[student])
        if sort_type == "1":
            students_new.sort(key=lambda x: x['math'], reverse=asc_or_desc)
            print("ID\t\t名字\t数学成绩\tPython成绩\t体育成绩\n")
            for student in students_new:
                print(student['ID'] + "\t" + student['name'] + "\t\t" + str(student['math']) + "\t\t" + str(
                    student['python']) + "\t\t" + str(student["sports"]))
        elif sort_type == "2":
            students_new.sort(key=lambda x: x["python"], reverse=asc_or_desc)
            print("ID\t\t名字\t数学成绩\tPython成绩\t体育成绩\n")
            for student in students_new:
                print(student['ID'] + "\t" + student['name'] + "\t\t" + str(student['math']) + "\t\t" + str(
                    student['python']) + "\t\t" + str(student["sports"]))
        elif sort_type == "3":
            students_new.sort(key=lambda x: x["sports"], reverse=asc_or_desc)
            print("ID\t\t名字\t数学成绩\tPython成绩\t体育成绩\n")
            for student in students_new:
                print(student['ID'] + "\t" + student['name'] + "\t\t" + str(student['math']) + "\t\t" + str(
                    student['python']) + "\t\t" + str(student["sports"]))
        elif sort_type == "0":
            students_new.sort(key=lambda x: x["math"] + x["python"] + x["sports"], reverse=asc_or_desc)
            print("ID\t\t名字\t数学成绩\tPython成绩\t体育成绩\n")
            for student in students_new:
                print(student['ID'] + "\t" + student['name'] + "\t\t" + str(student['math']) + "\t\t" + str(
                    student['python']) + "\t\t" + str(student["sports"]))
        else:
            print("输入错误")
        input_mark = input("是否继续排序？ (y/n) :")
        if input_mark == "y":
            continue
        else:
            break


# 学生成绩统计函数
def statistics():
    while True:
        sta_type = input("查看哪门科目分数的统计（1.数学 2.Python 3.体育 0.平均分）")
        a_flag = 0
        b_flag = 0
        c_flag = 0
        d_flag = 0
        e_flag = 0
        if sta_type == "1":
            print("数学 的成绩统计如下")
            for student in students_dict:
                if 90 <= students_dict[student]['math'] <= 100:
                    a_flag = a_flag + 1.0
                elif 80 <= students_dict[student]['math'] < 90:
                    b_flag = b_flag + 1.0
                elif 70 <= students_dict[student]['math'] < 80:
                    c_flag = c_flag + 1.0
                elif 60 <= students_dict[student]['math'] < 70:
                    d_flag = d_flag + 1.0
                else:
                    e_flag = e_flag + 1.0
        elif sta_type == "2":
            print("Python 的成绩统计如下")
            for student in students_dict:
                if 90 <= students_dict[student]['python'] <= 100:
                    a_flag = a_flag + 1.0
                elif 80 <= students_dict[student]['python'] < 90:
                    b_flag = b_flag + 1.0
                elif 70 <= students_dict[student]['python'] < 80:
                    c_flag = c_flag + 1.0
                elif 60 <= students_dict[student]['python'] < 70:
                    d_flag = d_flag + 1.0
                else:
                    e_flag = e_flag + 1.0
        elif sta_type == "3":
            print("体育 的成绩统计如下")
            for student in students_dict:
                if 90 <= students_dict[student]['sports'] <= 100:
                    a_flag = a_flag + 1.0
                elif 80 <= students_dict[student]['sports'] < 90:
                    b_flag = b_flag + 1.0
                elif 70 <= students_dict[student]['sports'] < 80:
                    c_flag = c_flag + 1.0
                elif 60 <= students_dict[student]['sports'] < 70:
                    d_flag = d_flag + 1.0
                else:
                    e_flag = e_flag + 1.0
        else:
            print("average 的成绩统计如下")
            for student in students_dict:
                score_all = (students_dict[student]['math']+students_dict[student]['python']+students_dict[student]['sports']) / 3.0
                if 90 <= score_all <= 100:
                    a_flag = a_flag + 1.0
                elif 80 <= score_all < 90:
                    b_flag = b_flag + 1.0
                elif 70 <= score_all < 80:
                    c_flag = c_flag + 1.0
                elif 60 <= score_all < 70:
                    d_flag = d_flag + 1.0
                else:
                    e_flag = e_flag + 1.0
        print("一共有 " + str(len(students_dict)) + " 名学生！")
        print("90分-100分" + str(a_flag) + "人，占总人数的 " + str(a_flag / len(students_dict)) + "\n")
        print("80分-90分" + str(b_flag) + "人，占总人数的 " + str(b_flag / len(students_dict)) + "\n")
        print("70分-80分" + str(c_flag) + "人，占总人数的 " + str(c_flag / len(students_dict)) + "\n")
        print("60分-70分" + str(d_flag) + "人，占总人数的 " + str(d_flag / len(students_dict)) + "\n")
        print("60分一下" + str(e_flag) + "人，占总人数的 " + str(e_flag / len(students_dict)) + "\n")

        input_mark = input("是否继续统计？ (y/n) :")
        if input_mark == "y":
            continue
        else:
            break


def main():
    while True:
        menu()  # 显示菜单
        option = input("请选择:")  # 选择菜单项
        option_str = re.sub(r"\D", "", option)  # 提取数字
        if option_str in ['0', '1', '2', '3', '4', '5', '6', '7']:
            option_int = int(option_str)
            if option_int == 0:  # 退出系统
                print('您已退出学生信息管理系统!')
                sys.exit()
            elif option_int == 1:  # 录入学生成绩信息
                insert()
            elif option_int == 2:  # 查找学生成绩信息
                search()
            elif option_int == 3:  # 删除学生成绩信息
                delete()
            elif option_int == 4:  # 修改学生成绩信息
                modify()
            elif option_int == 5:  # 排序
                sort()
            elif option_int == 6:  # 统计学生总数
                statistics()
            elif option_int == 7:  # 显示所有学生信息
                show()


if __name__ == '__main__':
    students_dict = {}
    main()


    添加文件git
