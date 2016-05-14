import java.io.*;
import java.util.*;

public class SortingTest
{
    //
    // Program entry point
    //
    public static void main(String args[])
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        try
        {
            boolean isRandom = false;	// 입력받은 배열이 난수인가 아닌가?
            int[] value;	// 입력 받을 숫자들의 배열
            String nums = br.readLine();	// 첫 줄을 입력 받음
            if (nums.charAt(0) == 'r')
            {
                // 난수일 경우
                isRandom = true;	// 난수임을 표시

                String[] nums_arg = nums.split(" ");

                int numsize = Integer.parseInt(nums_arg[1]);	// 총 갯수
                int rminimum = Integer.parseInt(nums_arg[2]);	// 최소값
                int rmaximum = Integer.parseInt(nums_arg[3]);	// 최대값

                Random rand = new Random();	// 난수 인스턴스를 생성한다.

                value = new int[numsize];	// 배열을 생성한다.
                for (int i = 0; i < value.length; i++)	// 각각의 배열에 난수를 생성하여 대입
                    value[i] = rand.nextInt(rmaximum - rminimum + 1) + rminimum;
            }
            else
            {
                // 난수가 아닐 경우
                int numsize = Integer.parseInt(nums);

                value = new int[numsize];	// 배열을 생성한다.
                for (int i = 0; i < value.length; i++)	// 한줄씩 입력받아 배열원소로 대입
                    value[i] = Integer.parseInt(br.readLine());
            }

            // 숫자 입력을 다 받았으므로 정렬 방법을 받아 그에 맞는 정렬을 수행한다.
            while (true)
            {
                int[] newvalue = (int[])value.clone();	// 원래 값의 보호를 위해 복사본을 생성한다.

                String command = br.readLine();

                long t = System.currentTimeMillis();
                switch (command.charAt(0))
                {
                    case 'B':	// Bubble Sort
                        newvalue = DoBubbleSort(newvalue);
                        break;
                    case 'I':	// Insertion Sort
                        newvalue = DoInsertionSort(newvalue);
                        break;
                    case 'H':	// Heap Sort
                        newvalue = DoHeapSort(newvalue);
                        break;
                    case 'M':	// Merge Sort
                        newvalue = DoMergeSort(newvalue);
                        break;
                    case 'Q':	// Quick Sort
                        newvalue = DoQuickSort(newvalue);
                        break;
                    case 'R':	// Radix Sort
                        newvalue = DoRadixSort(newvalue);
                        break;
                    case 'X':
                        return;	// 프로그램을 종료한다.
                    default:
                        throw new IOException("잘못된 정렬 방법을 입력했습니다.");
                }
                if (isRandom)
                {
                    // 난수일 경우 수행시간을 출력한다.
                    System.out.println((System.currentTimeMillis() - t) + " ms");
                }
                else
                {
                    // 난수가 아닐 경우 정렬된 결과값을 출력한다.
                    for (int i = 0; i < newvalue.length; i++)
                    {
                        System.out.println(newvalue[i]);
                    }
                }

            }
        }
        catch (IOException e)
        {
            System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
        }
    }

    // Swap function
    private static void swap(int[] array, int idx1, int idx2) {
        int temp = array[idx1];
        array[idx1] = array[idx2];
        array[idx2] = temp;
    }

    // Bubble sort
    private static int[] DoBubbleSort(int[] arr)
    {
        // TODO: 한 이터레이션 안에서 swap이 없었을경우 바로 종료하도록

        for (int iter = 0; iter < arr.length - 1; ++iter) {
            for (int i = 0; i < arr.length - 1 - iter; ++i) {
                if (arr[i] <= arr[i+1]) { continue; }
                swap(arr, i, i+1);
            }
        }

        return arr;
    }

    // Insertion sort
    private static int[] DoInsertionSort(int[] arr)
    {
        for (int i = 1; i < arr.length; ++i) {
            int j = i;
            while (j > 0 && arr[j-1] > arr[j]) {
                swap(arr, j, j-1);
                --j;
            }
        }

        return arr;
    }

    // Heap sort
    private static int[] DoHeapSort(int[] arr) {
        // Build heap
        for (int i = 0; i < arr.length; ++i) { heap_up(arr, i); }

        // Pop it
        for (int i = arr.length - 1; i > 0; --i) {
            swap(arr, 0, i);
            heap_fix(arr, i, 0);
        }

        return arr;
    }
    private static void heap_up(int[] arr, int idx) {
        // Base case
        if (idx == 0) { return; }

        int up = heap_parent(idx);
        if (arr[up] >= arr[idx]) { return; }

        swap(arr, up, idx);
        heap_up(arr, up);
    }
    private static void heap_fix(int[] arr, int size, int idx) {
        int max = idx,
            lhs = heap_left(idx),
            rhs = heap_right(idx);

        if (lhs < size && arr[lhs] > arr[max]) { max = lhs; }
        if (rhs < size && arr[rhs] > arr[max]) { max = rhs; }

        if (max == idx) { return; }
        swap(arr, idx, max);
        heap_fix(arr, size, max);
    }
    private static int heap_parent(int n) { return (n + 1)/2 - 1; }
    private static int heap_left  (int n) { return n*2 + 1; }
    private static int heap_right (int n) { return n*2 + 2; }

    // Merge sort
    private static int[] DoMergeSort(int[] arr) {
        merge_sort(arr, 0, arr.length);
        return arr;
    }
    private static void merge_sort(int[] arr, int begin, int end) {
        // Base case
        if (end - begin <= 1) { return; }

        // Recursion
        int mid = (begin + end)/2;
        merge_sort(arr, begin, mid);
        merge_sort(arr, mid, end);

        // Merge [begin, mid) and [mid, end)
        int[] buf = new int[end - begin];
        int idx = 0,
            lhs = begin,
            rhs = mid;

        while (lhs < mid && rhs < end) {
            buf[idx++] = arr[arr[lhs] <= arr[rhs] ? lhs++ : rhs++];
        }
        while (lhs < mid) { buf[idx++] = arr[lhs++]; }
        while (rhs < end) { buf[idx++] = arr[rhs++]; }

        // Copy back
        System.arraycopy(buf, 0, arr, begin, end - begin);
    }

    // Quick sort
    private static int[] DoQuickSort(int[] arr) {
        quick_sort(arr, 0, arr.length - 1);
        return arr;
    }
    private static void quick_sort(int[] arr, int lo, int hi) {
        // Base case
        if (lo >= hi) { return; }

        int p = partition(arr, lo, hi);
        quick_sort(arr, lo, p);
        quick_sort(arr, p + 1, hi);
    }
    private static int partition(int[] arr, int lo, int hi) {
        int pivot = arr[lo],
            i = lo - 1,
            j = hi + 1;

        while (true) {
            do { ++i; } while (arr[i] < pivot);
            do { --j; } while (arr[j] > pivot);
            if (i >= j) { return j; }
            swap(arr, i, j);
        }
    }

    // Radix sort
    private static int[] DoRadixSort(int[] arr) {
        radix_sort(arr, 4, 256);
        return arr;
    }
    private static void radix_sort(int[] arr, int digits, int base) {
        int[] counts = new int[base*2],
              tmp = new int[arr.length];

        // Iterate over digits
        for (int n = 0; n < digits; ++n) {
            Arrays.fill(counts, 0);
            final int pval = (int)Math.pow(base, n);
            // Count sort
            for (int j = 0; j < arr.length; ++j) { ++counts[base + (arr[j] / pval) % base]; }
            for (int i = 1; i < counts.length; ++i) { counts[i] += counts[i - 1]; }
            for (int j = arr.length - 1; j >= 0; --j) {
                int idx = base + (arr[j] / pval) % base;
                tmp[counts[idx] - 1] = arr[j];
                --counts[idx];
            }
            System.arraycopy(tmp, 0, arr, 0, arr.length);
        }
    }
}
