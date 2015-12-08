// 2013-11392 김지현

public class MyMatrix extends Tensor {
    public final MyVector[] rows;

    public MyMatrix(MyVector[] data) { rows = data.clone(); }

    public MyMatrix(int[][] input) {
        rows = new MyVector[input.length];
        for (int i = 0; i < rows.length; ++i) {
            rows[i] = new MyVector(input[i]);
        }
    }

    public Tensor add(Tensor right) {
        if (right instanceof MyMatrix) {
            MyMatrix r = (MyMatrix)right;

            // 길이 무조건 같음
            MyVector[] ret = new MyVector[r.rows.length];
            for (int y = 0; y < ret.length; ++y) {
                ret[y] = (MyVector)rows[y].add(r.rows[y]);
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

            int[] arr = new int[rows[0].data.length];
            for (int i = 0; i < arr.length; ++i) { arr[i] = 0; }
            Tensor ret = new MyVector(arr);

            for (int k = 0; k < arr.length; ++k) {
                int[] left = new int[rows.length];
                for (int i = 0; i < left.length; ++i) {
                    left[i] = rows[i].data[k];
                }

                ret = ret.add(new MyVector(left).multiply(new MyScalar(r.data[k])));
            }

            return ret;
        } else if (right instanceof MyMatrix) {
            MyMatrix r = (MyMatrix)right;

            int[][] mat = new int[this.rows.length][r.rows[0].data.length];
            for (int i = 0; i < mat.length; ++i) {
                for (int j = 0; j < mat[i].length; ++j) {
                    int sum = 0;
                    for (int k = 0; k < r.rows.length; ++k) {
                        sum += rows[i].data[k] * r.rows[k].data[j];
                    }
                    mat[i][j] = sum;
                }
            }

            return new MyMatrix(mat);
        } else {
            return null;
        }
    }

    public String toString() {
        StringBuffer buf = new StringBuffer();
        buf.append("Matrix");
        for (MyVector row: rows) {
            buf.append('\n');

            StringBuffer linebuf = new StringBuffer();
            for (int elem: row.data) {
                linebuf.append(elem);
                linebuf.append(' ');
            }
            buf.append(linebuf.toString().trim());
        }
        return buf.toString();
    }
}
