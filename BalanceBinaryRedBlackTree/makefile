OBJS=$(patsubst %.c, %.o, $(wildcard ./*.c))
# 变量定义赋值
TARGET=main

LDFLAGS=-L./src_so -L./src_a
LIBS=-lMyAdd -lMyDiv

SO_DIR=./src_so
A_DIR=./src_a

#变量取值用$()
$(TARGET):$(OBJS)
	$(CC) -g $^ -o $@

# 模式匹配: %目标:%依赖
%.o:%.c
	$(CC) -g -c $^ -o $@

all:
	make -C $(SO_DIR)
	make -C $(A_DIR)

# 伪目标/伪文件
.PHONY:	clean

clean:
	$(RM) $(OBJS) $(TARGET)

	
# wildcard : 匹配文件 			(获取指定目录下所有的.c文件)
# patsubst : 模式匹配与替换 	（指定目录下所有的.c文件替换成.o文件）
show:
	@echo $(wildcard ./*.c)
	@echo $(patsubst %.c, %.o, $(wildcard ./*.c))