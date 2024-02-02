# 自定义变量
# 变量赋值
OBJ=$(patsubst %.c, %.o, $(wildcard ./*.c))
OBJLIB=all

TARGET=main

LDFALGS=-L./src_so -L./src_a
LIBS=-lSoMyAdd -lMyDiv

SO_DIR=./src_so 
A_DIR=./src_a

# 使用$(TARGET) 必须要加 '$' 符号
$(TARGET):$(OBJ)
	$(CC) -g $^ -o $@

# 模式匹配
%.o:%.c
	$(CC) -g -c $^ -o $@

all:
	$(MAKE) -C $(SO_DIR)
	$(MAKE) -C $(A_DIR)

# 伪文件 / 伪目标
.PHONY:	clean

# 清除编译出来的依赖文件 和 二进制文件
clean:
	@$(RM) *.o $(TARGET)
	$(MAKE) -C $(SO_DIR) clean
	$(MAKE) -C $(A_DIR) clean


show:
	@echo $(RM)
	@echo $(CC)
	@echo $(CXX)
	@echo $(MAKE)
	@echo $(wildcard ./*.c)
	@echo $(patsubst %.c, %.o, $(wildcard ./*.c))