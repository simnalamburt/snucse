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

            int[][] mat = r.data.clone();
            for (int y = 0; y < mat.length; ++y) {
                for (int x = 0; x < mat[y].length; ++x) {
                    mat[y][x] += data;
                }
            }

            return new MyMatrix(mat);
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

            int[][] mat = r.data.clone();
            for (int y = 0; y < mat.length; ++y) {
                int[] arr = mat[y];
                for (int x = 0; x < arr.length; ++x) {
                    arr[x] *= data;
                }
            }

            return new MyMatrix(mat);
        } else {
            return null;
        }
    }

    public String toString() {
        return String.format("Scalar %d", data);
    }
}
