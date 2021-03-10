<h1 align="center">Hash Table Report</h1>
<h3 align="center">Md. Zarif Ul Alam : 1705010</h3>

## Hash Functions
```c++
int hashF1(string s)
{
    int h = 0 , p = 31;
    for(int i=0;i<(int)s.size();i++)
    {
        h = (h * p + s[i]);
    }
    return h;
}
```
```c++
int hashF2(string s)
{
    int h = 0 , prime = 31 , p = 1 , mod = 1e9+7;
    for(int i=0;i<(int)s.size();i++)
    {
        h = ((h%mod) + (p * s[i])%mod) % mod;

        p = ((p%mod) * (prime%mod))%mod;
    }
    return h;
}
```

&nbsp;
## Auxilary Hash Function
```c++
int auxhashF(string s)
{
    int h = 7 , p = 31;
    for(int i=0;i<(int)s.size();i++)
    {
        h = (h * p + s[i]);
    }
    return h;
}
```

&nbsp;
## Probe Functions
```c++
int doubleHashingProbe(int x,int aux)
{
    return x*aux;
}
int customHashingProbe(int x,int aux)
{
    return (x*aux + x*x)>>1;
}
```
&nbsp;

## Collision and Avg. Probe Report 
&nbsp;

<table class="table_">
		<tbody class="calibre1"><tr class="calibre2">
			<td rowspan="2" class="td_"><p class="block_"><span class="text_">Collision Resolution Method</span></p></td>
			<td colspan="2" class="td_1"><p class="block_"><span class="text_">Hash1</span></p></td>
			<td colspan="2" class="td_2"><p class="block_"><span class="text_">Hash2</span></p></td>
		</tr>
		<tr class="calibre2">
			<td class="td_3"><p class="block_"><span class="text_">No. of Collisions</span></p></td>
			<td class="td_4"><p class="block_"><span class="text_">Avg. Probes</span></p></td>
			<td class="td_5"><p class="block_"><span class="text_">No. of Collisions</span></p></td>
			<td class="td_6"><p class="block_"><span class="text_">Avg. Probes</span></p></td>
		</tr>
		<tr class="calibre2">
			<td class="td_7"><p class="block_"><span class="text_">Chaining Method</span></p></td>
			<td class="td_3"><p class="block_"><span class="text_">3632</span></p></td>
			<td class="td_4"><p class="block_"><span class="text_">1.54</span></p></td>
			<td class="td_5"><p class="block_"><span class="text_">3648</span></p></td>
			<td class="td_6"><p class="block_"><span class="text_">1.53</span></p></td>
		</tr>
		<tr class="calibre2">
			<td class="td_7"><p class="block_"><span class="text_">Double Hashing</span></p></td>
			<td class="td_3"><p class="block_"><span class="text_">63718</span></p></td>
			<td class="td_4"><p class="block_"><span class="text_">5.61</span></p></td>
			<td class="td_5"><p class="block_"><span class="text_">57889</span></p></td>
			<td class="td_6"><p class="block_"><span class="text_">5.57</span></p></td>
		</tr>
		<tr class="calibre2">
			<td class="td_8"><p class="block_"><span class="text_">Custom Probing</span></p></td>
			<td class="td_9"><p class="block_"><span class="text_">62598</span></p></td>
			<td class="td_10"><p class="block_"><span class="text_">6.71</span></p></td>
			<td class="td_11"><p class="block_"><span class="text_">62388</span></p></td>
			<td class="td_12"><p class="block_"><span class="text_">5.73</span></p></td>
		</tr>
	</tbody>
</table>


