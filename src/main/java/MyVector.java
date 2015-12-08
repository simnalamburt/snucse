// 2013-11392 김지현

import java.util.Arrays;

public class MyVector extends Tensor {
    public final int[] data;

    public MyVector(int[] input) { data = input.clone(); }

    public boolean permuteCompare(MyVector right) {
        int[] v1 = this.data.clone();
        int[] v2 = right.data.clone();

        Arrays.sort(v1);
        Arrays.sort(v2);

        for (int i = 0; i < v1.length; ++i) {
            if (v1[i] != v2[i]) { return false; }
        }
        return true;
    }

    public Tensor add(Tensor right) {
        if (right instanceof MyVector) {
            // 길이 다른경우 없음
            MyVector r = (MyVector)right;

            int[] arr = r.data.clone();
            for (int i = 0; i < arr.length; ++i) {
                arr[i] += data[i];
            }

            return new MyVector(arr);
        } else if (right instanceof MyMatrix) {
            MyMatrix r = (MyMatrix)right;

            MyVector[] ret = new MyVector[r.rows.length];
            for (int y = 0; y < ret.length; ++y) {
                ret[y] = (MyVector)this.add(r.rows[y]);
            }

            return new MyMatrix(ret);
        } else {
            return right.add(this);
        }
    }

    public Tensor multiply(Tensor right) {
        if (right instanceof MyScalar) {
            return right.multiply(this);
        } else if (right instanceof MyVector) {
            MyVector r = (MyVector)right;

            int ret = 0;
            for (int i = 0; i < data.length; ++i) {
                ret += data[i] * r.data[i];
            }

            return new MyScalar(ret);
        } else if (right instanceof MyMatrix) {
            MyMatrix r = (MyMatrix)right;

            int[] arr = new int[r.rows[0].data.length];
            for (int i = 0; i < arr.length; ++i) { arr[i] = 0; }
            Tensor ret = new MyVector(arr);

            for (int k = 0; k < data.length; ++k) {
                ret = ret.add(new MyScalar(data[k]).multiply(r.rows[k]));
            }

            return ret;
        } else {
            return null;
        }
    }

    public String toString() {
        StringBuffer buf = new StringBuffer();
        buf.append("Vector");
        for (int elem: data) {
            buf.append(' ');
            buf.append(elem);
        }
        return buf.toString();
    }
}
