#include "class1.h"
#include "fastgr.h"
#include <iostream>

void Class1::class1(graph_t *g) {

    node_it n, vi_end;
    in_edge_iterator ei, ei_end;
    out_edge_iterator eo, eo_end;

    //迭代获取每个顶点的入边和出边,存到vector中 out_edges() 迭代获取顶点的所有出边  in_edges(),   这些迭代器被称为出边迭代器，解除对其中一个迭代器的引用就会得到一个边描述符对象。
    for (boost::tie(n, vi_end) = vertices(*g); n != vi_end; ++n) {
        for (boost::tie(eo, eo_end) = boost::out_edges(*n, *g); eo != eo_end; ++eo) {
            boost::get(*orig_out_map, *n).push_back(*eo);
        }
        for (boost::tie(ei, ei_end) = boost::in_edges(*n, *g); ei != ei_end; ++ei) {
            boost::get(*orig_in_map, *n).push_back(*ei);
        }
    }

    for (boost::tie(n, vi_end) = vertices(*g); n != vi_end; ++n) {
        std::vector<edge_t> &orig_out_n = boost::get(*orig_out_map, *n);
        for (std::vector<edge_t>::iterator it = orig_out_n.begin(); it != orig_out_n.end(); ++it) { // using vector here instead of boost::out_edges() is so smart!
            if (boost::get(*to_virt_map, *it) != edge_t()) // I assume that it does not happen
                continue;
            // assume that there are no UF_union() actions have been performed
            node_t end_node = boost::target(*it, *g);
            fastgraph fg(g, propmap);
            edge_t fast_edge_found = fg.find_fast_edge(*n, end_node); //找到一条u,v 之间的边就返回,否则返回edge_t() 
            if (fast_edge_found != edge_t()) {
                fg.merge_oneway(*it, fast_edge_found);//互相赋值
            } else {
                fg.virtual_edge(*n, end_node, *it);//加虚拟边  将虚拟图中的边和原始边一一对应  通过k v 的形式即可找到
            }
        }
    }    

}

