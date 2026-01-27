import random
import time
import matplotlib.pyplot as plt

print("="*70)
print("Part 1: Python list operations")
print("="*70)

sample_list = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
print("Original list:", sample_list)

# Append an element
sample_list.append(10)
print("After appending 10:", sample_list)

# clear the list
sample_list.clear()
print("After clearing the list:", sample_list)

# Re-initialize the list for further operations
sample_list = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
# copy the list
copied_list = sample_list.copy()
print("Copied list:", copied_list)

# count occurrences of an element
count_of_5 = sample_list.count(5)
print("Count of 5 in the list:", count_of_5)

# extend the list with another list
sample_list.extend([7, 8, 9])
print("After extending with [7, 8, 9]:", sample_list)

# find index of an element
index_of_9 = sample_list.index(9)
print("Index of 9 in the list:", index_of_9)

# pop an element
popped_element = sample_list.pop()
print("Popped element:", popped_element)
print("List after popping an element:", sample_list)

# remove an element
sample_list.remove(1)
print("After removing first occurrence of 1:", sample_list)

# reverse the list
sample_list.reverse()
print("Reversed list:", sample_list)

# sort the list
sample_list.sort()
print("Sorted list:", sample_list)

print("\n" + "="*70)
print("="*70)
print("Part 2: Performance comparison")
print("="*70)

base_N = 1000
sizes = [base_N * m for m in [1, 2, 4, 8, 16, 32]]

pop_end_times = []
pop_front_times = []
slice_copy_times = []
list_copy_times = []
reverse_inplace_times = []
reverse_slice_times = []

for N in sizes:
    print(f"\nN = {N:,}")
    
    times = []
    for _ in range(100):
        L = [random.randint(0, 1000000) for _ in range(N)]
        start = time.perf_counter()
        L.pop()
        end = time.perf_counter()
        times.append(end - start)
    avg = sum(times) / len(times)
    pop_end_times.append(avg)
    print(f"  L.pop():     {avg*1e6:.2f} us")
    
    times = []
    for _ in range(100):
        L = [random.randint(0, 1000000) for _ in range(N)]
        start = time.perf_counter()
        L.pop(0)
        end = time.perf_counter()
        times.append(end - start)
    avg = sum(times) / len(times)
    pop_front_times.append(avg)
    print(f"  L.pop(0):    {avg*1e6:.2f} us")
    
    L = [random.randint(0, 1000000) for _ in range(N)]
    times = []
    for _ in range(100):
        start = time.perf_counter()
        A = L[:]
        end = time.perf_counter()
        times.append(end - start)
    avg = sum(times) / len(times)
    slice_copy_times.append(avg)
    print(f"  A = L[:]:    {avg*1e6:.2f} us")
    
    times = []
    for _ in range(100):
        start = time.perf_counter()
        B = list(L)
        end = time.perf_counter()
        times.append(end - start)
    avg = sum(times) / len(times)
    list_copy_times.append(avg)
    print(f"  B = list(L): {avg*1e6:.2f} us")
    
    times = []
    for _ in range(100):
        L = [random.randint(0, 1000000) for _ in range(N)]
        start = time.perf_counter()
        L.reverse()
        end = time.perf_counter()
        times.append(end - start)
    avg = sum(times) / len(times)
    reverse_inplace_times.append(avg)
    print(f"  L.reverse(): {avg*1e6:.2f} us")
    
    times = []
    for _ in range(100):
        L = [random.randint(0, 1000000) for _ in range(N)]
        start = time.perf_counter()
        R = L[::-1]
        end = time.perf_counter()
        times.append(end - start)
    avg = sum(times) / len(times)
    reverse_slice_times.append(avg)
    print(f"  R = L[::-1]: {avg*1e6:.2f} us")

print("\n" + "="*70)
print("Part 3: Plotting results")
print("="*70)

fig, axes = plt.subplots(2, 2, figsize=(8,6))
sizes_k = [s // 1000 for s in sizes]

axes[0, 0].plot(sizes_k, [t*1e6 for t in pop_end_times], 'b-o', label='L.pop()')
axes[0, 0].plot(sizes_k, [t*1e6 for t in pop_front_times], 'r-s', label='L.pop(0)')
axes[0, 0].set_xlabel('List Size (thousands)')
axes[0, 0].set_ylabel('Time (us)')
axes[0, 0].set_title('Cost of Removing Elements')
axes[0, 0].legend()
axes[0, 0].grid(True)

axes[0, 1].plot(sizes_k, [t*1e6 for t in slice_copy_times], 'g-o', label='A = L[:]')
axes[0, 1].plot(sizes_k, [t*1e6 for t in list_copy_times], 'm-s', label='B = list(L)')
axes[0, 1].set_xlabel('List Size (thousands)')
axes[0, 1].set_ylabel('Time (us)')
axes[0, 1].set_title('Slicing vs Explicit Copy')
axes[0, 1].legend()
axes[0, 1].grid(True)

axes[1, 0].plot(sizes_k, [t*1e6 for t in reverse_inplace_times], 'c-o', label='L.reverse()')
axes[1, 0].plot(sizes_k, [t*1e6 for t in reverse_slice_times], 'orange', marker='s', label='R = L[::-1]')
axes[1, 0].set_xlabel('List Size (thousands)')
axes[1, 0].set_ylabel('Time (us)')
axes[1, 0].set_title('In-place vs Out-of-place Reverse')
axes[1, 0].legend()
axes[1, 0].grid(True)

axes[1, 1].loglog(sizes, [t*1e6 for t in pop_end_times], 'b-o', label='pop()')
axes[1, 1].loglog(sizes, [t*1e6 for t in pop_front_times], 'r-s', label='pop(0)')
axes[1, 1].loglog(sizes, [t*1e6 for t in slice_copy_times], 'g-^', label='L[:]')
axes[1, 1].loglog(sizes, [t*1e6 for t in reverse_inplace_times], 'c-d', label='reverse()')
axes[1, 1].set_xlabel('List Size')
axes[1, 1].set_ylabel('Time (us)')
axes[1, 1].set_title('All Operations (Log-Log Scale)')
axes[1, 1].legend()
axes[1, 1].grid(True)

plt.tight_layout()
plt.savefig('lab03_performance.png', dpi=150)
print("\nPlot saved as 'lab03_performance.png'")

print("\n" + "="*70)
print("Part 4: Observations")
print("="*70)
print("""
1. L.pop() vs L.pop(0):
   
   pop() just removes the last item, so it's super fast and stays constant
   no matter how big the list is.
   
   pop(0) removes the first item, but then every other element has to 
   slide over one spot to fill the gap. If you have 320,000 items, that's
   319,999 elements moving. That's why it gets slower as N increases.

2. A = L[:] vs B = list(L):
   
   Both do the same thing - make a fresh copy of the list. The times are
   almost identical because they're doing the same work behind the scenes.
   Just pick whichever you find more readable.

3. L.reverse() vs R = L[::-1]:
   
   reverse() flips the list in place by swapping elements directly. No new
   memory needed, so it's quick.
   
   L[::-1] has to create a whole new list and copy everything over in 
   reverse order. Allocating that extra memory takes time, which is why
   it's noticeably slower.
   
   Use reverse() if you don't need the original anymore.
   Use L[::-1] if you want to keep the original list intact.
""")