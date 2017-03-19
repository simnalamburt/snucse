import os
import gzip
import pickle
from urllib import request
import numpy as np

#
# Constants
#
URL_BASE = 'http://yann.lecun.com/exdb/mnist/'

TRAIN_IMG   = 'train-images-idx3-ubyte.gz'
TRAIN_LABEL = 'train-labels-idx1-ubyte.gz'
TEST_IMG    = 't10k-images-idx3-ubyte.gz'
TEST_LABEL  = 't10k-labels-idx1-ubyte.gz'

DATASET_DIR = os.path.dirname(__file__)
CACHE_PATH = DATASET_DIR + "/mnist.pkl"


def download():
    """
    MNIST 데이터셋을 다운받는 함수.

    저장된 MNIST 캐시가 있을경우 캐시를 사용하고, 캐시된 파일이 없을경우
    <http://yann.lecun.com/exdb/mnist/>에서 새 데이터를 받아 이를 pickle
    포맷으로 변환하여 캐싱한다.
    """

    # 저장된 MNIST 데이터 캐시가 있을경우, 이를 사용한다.
    if os.path.exists(CACHE_PATH):
        with open(CACHE_PATH, 'rb') as f:
            return pickle.load(f)

    # 저장된 캐시가 없으므로, 네개의 MNIST 데이터 파일을 차례대로 다운받는다.
    for file_name in [TRAIN_IMG, TRAIN_LABEL, TEST_IMG, TEST_LABEL]:
        path = os.path.join(DATASET_DIR, file_name)

        # 이미 다운받은 파일일경우 생략한다.
        if not os.path.exists(path):
            request.urlretrieve(URL_BASE + file_name, path)

    def load(callback):
        def func(file_name):
            path = os.path.join(DATASET_DIR, file_name)
            with gzip.open(path, 'rb') as file:
                return callback(file)
        return func
    load_label = load(lambda file: np.frombuffer(file.read(), np.uint8, offset=8))
    load_img = load(lambda file: np\
                    .frombuffer(file.read(), np.uint8, offset=16)\
                    .reshape(-1, 784))

    # 데이터들을 하나의 딕셔너리로 합친다.
    dataset = {
        'train_img'   : load_img(TRAIN_IMG),
        'train_label' : load_label(TRAIN_LABEL),
        'test_img'    : load_img(TEST_IMG),
        'test_label'  : load_label(TEST_LABEL),
    }

    # Pickle 포맷으로 저장한다.
    with open(CACHE_PATH, 'wb') as f:
        pickle.dump(dataset, f, -1)

    return dataset


def load(normalize=True, flatten=True, one_hot_label=True):
    """
    MNIST 데이터셋을 로드하는 함수.

    저장된 MNIST 캐시가 있을경우 캐시를 사용하고, 캐시된 파일이 없을경우
    <http://yann.lecun.com/exdb/mnist/>에서 새 데이터를 받아 이를 pickle
    포맷으로 변환하여 캐싱한다.

    :normalize:     `True` 일 경우, 이미지의 픽셀 값을 `[0.0, 1.0]` 구간 안에
                    들어가는 값으로 정규화한다. 그렇지 않을경우, `[0, 256)`
                    구간의 정수를 반환한다.
    :one_hot_label: `True` 일 경우, 레이블을 One-hot encode 한다.
    :flatten:       `True` 일 경우, 입력 이미지를 1차원 배열로 flatten 한다.
    :Returns:       `(훈련 이미지, 훈련 레이블), (시험 이미지, 시험 레이블)`
    """

    # MNIST 데이터를 로드한다.
    dataset = download()

    # [0.0, 1.0] 구간 안에 들어가도록 이미지를 정규화한다.
    if normalize:
        for key in ('train_img', 'test_img'):
            dataset[key] = dataset[key].astype(np.float32) / 255.0

    # One-hot encode한다.
    if one_hot_label:
        def one_hot_encode(X):
            array = np.zeros((X.size, 10))
            for idx, row in enumerate(array):
                row[X[idx]] = 1
            return array
        for key in ('train_label', 'test_label'):
            dataset[key] = one_hot_encode(dataset[key])

    # 1차원 배열로 flatten한다.
    if not flatten:
        for key in ('train_img', 'test_img'):
            dataset[key] = dataset[key].reshape(-1, 1, 28, 28)

    return dataset
