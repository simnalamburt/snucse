clear;
load('MNIST_Dataset.mat');

train_x = trainingData.Images(:,1:1000)';
train_c = trainingData.Labels(1:1000,:);
test_img = testingData.Images(:,1:100)';
test_label = testingData.Labels(1:100,:);

p_class = zeros(1,10);
p_test_x1 = zeros(1,10);
train_subx = cell(10);
mu = cell(10);
sigma = cell(10);

%
% Training
%
for j = 1:10
    train_subx{j} = train_x(train_c==mod(j,10),:);
    mu{j} = mean(train_subx{j});
    sigma{j} = cov(train_subx{j})+0.1*eye(size(train_x,2));
    p_class(j) = size(train_subx{j},1)/size(train_x,1);
end
for j = 1:10
    p_test_x1(j) = p_class(j)*mvnpdf(test_img(1,:),mu{j},sigma{j});
end

confusion_matrix = zeros(10,10);
% row: test_label
% col: estimate of the classifier
p_likelihood = zeros(10, size(test_img,1));
for j = 1:10
    p_likelihood(j,:) = p_class(j)*mvnpdf(test_img,mu{j},sigma{j});
end
[max_val, max_idx] = max(p_likelihood);
for i=1:size(test_img,1)
    if test_label(i) == 0
        confusion_matrix(10, max_idx(i)) = confusion_matrix(10, max_idx(i)) + 1;
    else
        confusion_matrix(test_label(i), max_idx(i)) = confusion_matrix(test_label(i), max_idx(i)) + 1;
    end
end
accuracy = sum(diag(confusion_matrix))/size(test_img,1);
display(accuracy);

% 0.93