// Swap two elements
void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// Insertion sort array A
void insertion_sort(int A[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
}

// Merge sort array A
void merge_sort(int A[], int n) {
    int i, j, k, m, *B;
    if (n > 1) {
        m = n / 2;
        B = (int *)malloc(m * sizeof(int));
        for (i = 0; i < m; i++)
            B[i] = A[i];
        merge_sort(B, m);
        for (i = m, j = 0; i < n; i++, j++)
            A[j] = A[i];
        merge_sort(A + m, n - m);
        for (i = 0, j = 0, k = 0; k < n; k++)
            if (j < m && (i >= n || B[j] <= A[i]))
                A[k] = B[j++];
            else
                A[k] = A[i++];
        free(B);
    }
}

// Max heapify array A
void max_heapify(int A[], int n, int i) {
    int l, r, largest;
    l = 2 * i + 1;
    r = 2 * i + 2;
    if (l < n && A[l] > A[i])
        largest = l;
    else
        largest = i;
    if (r < n && A[r] > A[largest])
        largest = r;
    if (largest != i) {
        swap(&A[i], &A[largest]);
        max_heapify(A, n, largest);
    }
}

// Build max heap array A
void build_max_heap(int A[], int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        max_heapify(A, n, i);
}

// Heap sort array A
void heap_sort(int A[], int n) {
    build_max_heap(A, n);
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        max_heapify(A, n, i);
    for (i = n - 1; i >= 0; i--) {
        swap(&A[0], &A[i]);
        max_heapify(A, i, 0);
    }
}

// Partition array A
int partition(int A[], int n, int p, int r) {
    int x, i, j;
    x = A[r];
    i = p - 1;
    for (j = p; j < r; j++)
        if (A[j] <= x) {
            i++;
            swap(&A[i], &A[j]);
        }
    swap(&A[i + 1], &A[r]);
    return i + 1;
}

// Quick sort array A
void quick_sort(int A[], int n, int p, int r) {
    int q;
    if (p < r) {
        q = partition(A, n, p, r);
        quick_sort(A, n, p, q - 1);
        quick_sort(A, n, q + 1, r);
    }
}

// Counting sort array A
void counting_sort(int A[], int B[], int n) {
    int i, j, k, *C;
    B = (int *)malloc(n * sizeof(int));
    C = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        C[i] = 0;
    for (i = 0; i < n; i++)
        C[A[i]]++;
    for (i = 1; i < n; i++)
        C[i] += C[i - 1];
    for (i = n - 1; i >= 0; i--) {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }
    free(B);
    free(C);
}