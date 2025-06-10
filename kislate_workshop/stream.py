from graphviz import Digraph

# 创建流程图对象
dot = Digraph(name="SubArrayNum_Flowchart", comment='SubArrayNum 流程图', format="png")
dot.graph_attr['rankdir'] = 'TB'  # Top to Bottom
dot.node_attr.update(shape='rectangle', style='rounded')

# 开始节点
dot.node('start', '开始', shape='ellipse')

# 初始化部分
dot.node('init_count_sum', '初始化 count = 0, sum = 0')
dot.node('init_offset', '设置偏移量 offset = 100000')
dot.node('init_mp', '定义哈希数组 mp[200001]，全部置为 0')
dot.node('mp_offset_1', 'mp[offset] = 1 （表示前缀和为 0 的情况出现一次）')

# 循环部分
dot.node('loop_start', 'i = 0')
dot.node('loop_condition', 'i < L.length?', shape='diamond')
dot.node('sum_add_elem', 'sum += L.elem[i]')
dot.node('calc_idx', 'idx = sum - k + offset')
dot.node('check_idx', 'idx ∈ [0, 200001)?', shape='diamond')
dot.node('count_add_mp', 'count += mp[idx]')
dot.node('mp_increment', 'mp[sum + offset]++')
dot.node('i_increment', 'i++')
dot.node('end', '返回 count', shape='ellipse')

# 连接节点
dot.edge('start', 'init_count_sum')
dot.edge('init_count_sum', 'init_offset')
dot.edge('init_offset', 'init_mp')
dot.edge('init_mp', 'mp_offset_1')
dot.edge('mp_offset_1', 'loop_start')
dot.edge('loop_start', 'loop_condition')

# 循环判断内的连接
dot.edge('loop_condition', 'sum_add_elem', label='是')
dot.edge('sum_add_elem', 'calc_idx')
dot.edge('calc_idx', 'check_idx')
dot.edge('check_idx', 'count_add_mp', label='是')
dot.edge('count_add_mp', 'mp_increment')
dot.edge('mp_increment', 'i_increment')
dot.edge('i_increment', 'loop_condition')
dot.edge('check_idx', 'mp_increment', label='否')
dot.edge('loop_condition', 'end', label='否')

# 保存并渲染图像
dot.render(filename='subarraynum_flowchart', view=True)
print("✅ 流程图已生成：subarraynum_flowchart.png")