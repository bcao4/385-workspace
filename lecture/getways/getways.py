def get_ways(numstairs):
    ways = []
    if numstairs <= 0:
        ways.append([])
    else:
        for i in range(1,4):
            if numstairs >= i:
                result = get_ways(numstairs - i)
                for j in range(len(result)):
                    result[j].append(i)
                ways += result
        return ways
        