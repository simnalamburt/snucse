// 2013-11392 김지현

public class MyScalar extends Tensor {
    public final int data;
    public MyScalar(int input) { data = input; }

    public Tensor add(Tensor right) {
        if (right instanceof MyScalar) {
            MyScalar r = (MyScalar)right;

            return new MyScalar(this.data + r.data);
        } else if (right instanceof MyVector) {
            MyVector r = (MyVector)right;

            int[] arr = r.data.clone();
            for (int i = 0; i < arr.length; ++i) {
                arr[i] += data;
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
            MyScalar r = (MyScalar)right;

            return new MyScalar(this.data * r.data);
        } else if (right instanceof MyVector) {
            MyVector r = (MyVector)right;

            int[] arr = r.data.clone();
            for (int i = 0; i < arr.length; ++i) {
                arr[i] *= data;
            }

            return new MyVector(arr);
        } else if (right instanceof MyMatrix) {
            MyMatrix r = (MyMatrix)right;

            MyVector[] ret = new MyVector[r.rows.length];
            for (int y = 0; y < ret.length; ++y) {
                ret[y] = (MyVector)this.multiply(r.rows[y]);
            }

            return new MyMatrix(ret);
        } else {
            return null;
        }
    }

    public String toString() {
        return String.format("Scalar %d", data);
    }
}
