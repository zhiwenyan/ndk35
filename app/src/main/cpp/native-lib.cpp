#include <jni.h>
#include <string>
#include <android/log.h>
#include "ArrayUtil.cpp"


void merge_(int *pInt, int l, int mid, int r);

extern "C" JNIEXPORT jstring

JNICALL
Java_com_steven_ndk35_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}


/**
 * 冒泡排序  比较相邻的元素。如果第一个比第二个大，就交换它们两个
 * 时间复杂度  空间复杂度
 *
 * 优化 鸡尾酒排序
 * @param arr
 * @param len
 */
void BubbleSort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {  //n-1步
        for (int j = 0; j < len - i - 1; j++) {  // n^2/2-n/2
            if (arr[j] > arr[j + 1]) {
                //交换一次 三次赋值
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}


/**
 * 选择排序
 * @param arr
 * @param len
 */
void selectSort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[minIndex] > arr[j]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);

    }
}

/**98
 * 插入排序 --
 * @param arr
 * @param len
 */
void insertSort(int arr[], int len) {
    for (int i = 1; i < len; i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                std::swap(arr[j], arr[j - 1]);
            } else {
                break;
            }
        }
    }
}

/**
 * 优化下插入排序
 * @param arr
 * @param len
 */
void insertSort1(int arr[], int len) {
    int j, i;
    for (i = 1; i < len; i++) {
        int temp = arr[i];
        for (j = i; j > 0; j--) {
            if (arr[j - 1] > temp) {
                arr[j] = arr[j - 1];
            } else {
                break;
            }
        }
        //插入适合的位置
        arr[j] = temp;
    }
}

// 希尔排序思想：对插入排序分组 过一下
void shellInsertSort(int arr[], int len) {// 8
    // 思考？  作业，求算法复杂度，
    // 1. 第一个多思考 （问题 10 分钟）
    // 2. 问大家解决思路 ：找到问题的原因（线上出了一个 Bug）
    // 3. 能不能这样改（原因去改）
    int increment = len / 2; // 4 组
    int i, j, k;
    while (increment >= 1) {
        // 希尔排序
        for (i = 0; i < increment; ++i) { // i = 0, increment = 2
            for (j = i + increment; j < len; j += increment) {
                int tmp = arr[j];
                for (k = j; k > i && arr[k - increment] > tmp; k -= increment) {
                    // 往后逻动
                    arr[k] = arr[k - increment];
                }
                arr[k] = tmp;
            }
        }
        increment /= 2;
    }
}

// 对数组的 [l,r] 区间进行归并排序
void mergeSort_(int arr[], int l, int r) {
    // 递归到底的情况
    if (l >= r) {
        return;
    }
    int mid = (l + r) >> 1;
    mergeSort_(arr, l, mid);
    mergeSort_(arr, mid + 1, r);
    // 优化要根据具体的场景去做
    if (arr[mid] > arr[mid + 1]) {
        merge_(arr, l, mid, r);
    }
}
// 对数组区间 [l,mid] 和 [mid+1,r] 进行归并

void merge_(int arr[], int l, int mid, int r) {
    // 1. 对数组进行一次拷贝
    int temp[r - l + 1];
    for (int i = l; i <= r; ++i) {
        temp[i - l] = arr[i];
    }
    // 2. 确定好分析之后的变量
    int i = l;
    int j = mid + 1;
    int k = l;
    for (; k <= r; ++k) {
        // 这个代码有没有问题？
        if (i > mid) {
            arr[k] = temp[j - l];
            j++;
        } else if (j > r) {
            arr[k] = temp[i - l];
            i++;
        }
            // 临时数据里面的 i 位置和 j 位置去比较
        else if (temp[i - l] < temp[j - l]) {
            arr[k] = temp[i - l];
            i++;
        } else {
            arr[k] = temp[j - l];
            j++;
        }
    }
}


void mergeSort(int arr[], int len) {
    mergeSort_(arr, 0, len - 1);

}

void quickSort(int arr[], int len) {

}


void print_array(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        __android_log_print(ANDROID_LOG_ERROR, "JNI_TAG", "arr: %d", arr[i]);

    }
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_steven_ndk35_sort_SortUtils_sort(JNIEnv *env, jclass type) {
    int len = 20000;
    int *arr = ArrayUtil::create_random_array(len, 20, 100);
    int *arr1 = ArrayUtil::copy_random_array(arr, len);
    int *arr2 = ArrayUtil::copy_random_array(arr, len);
    int *arr3 = ArrayUtil::copy_random_array(arr, len);
    int *arr4 = ArrayUtil::copy_random_array(arr, len);
    int *arr5 = ArrayUtil::copy_random_array(arr, len);

    //mergeSort(arr, len);
    //  print_array(arr, len);
    //对冒泡排序和选择排序进行性能测试
    ArrayUtil::sort_array("BubbleSort", BubbleSort, arr, len);  //6.1s

    ArrayUtil::sort_array("selectSort", selectSort, arr1, len);  //  3.04s


    ArrayUtil::sort_array("insertSort", insertSort, arr2, len);  // 3.73s
    //如果对于接近排好的序数据，时间复杂度接近O(n)，考虑最坏的情况是O(n^2)
    ArrayUtil::sort_array("insertSort1", insertSort1, arr3, len);  // 2.38s

    ArrayUtil::sort_array("shellInsertSort", shellInsertSort, arr4, len); //0.014

    ArrayUtil::sort_array("mergeSort", mergeSort, arr5, len); //0.016
    delete[](arr);
    delete[](arr1);
    delete[](arr2);
    delete[](arr3);

    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}