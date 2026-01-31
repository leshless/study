M = 15

def hash1(val):
    return val % M

def hash2(val):
    return (val // M) % M

def benchmark(h):
    values = list(map(int, "30 31 15 79 55 42 99 60 80 23 43 53".split(" ")))

    table = ["X" for _ in range(15)]
    probes = 0
    for v in values:
        for i in range(0, M):
            j = h(v, i)

            if table[j] == "X":
                break

        probes += i+1
        table[j] = v

    clusters = []
    cur_cluster = 0
    for x in table:
        if x == 'X' and cur_cluster != 0:
            clusters.append(cur_cluster)
            cur_cluster = 0
            continue
        cur_cluster += 1

    if table[0] != 'X':
        clusters[0] += cur_cluster
    else:
        clusters.append(cur_cluster)


    print(f"Result: {table}")
    print(f"Load Factor: {len(values)/M}")
    print(f"Probes Total: {probes}")
    print(f"Probes Average: {probes/len(values)}")
    print(f"Clusters: {len(clusters)}")
    print(f"Cluster Size Average: {sum(clusters)/len(clusters)}")

print("Linear probing")
benchmark(lambda v,i : (hash1(v) + i) % M)

print("")

print("Double Hashing")
benchmark(lambda v,i : (hash1(v) + i * hash2(v)) % M)