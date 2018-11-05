#include "network.h"
#include "random.h"
#include <algorithm>

#include <iostream>


void Network::resize(const size_t& &n)
{
	if(size() > n)
	{
		for(size_t i(size()-1); i<n; ++i)
		{
			links.erase(i);
			auto erasedNode = links.equal_range(i);
			for(auto I = eraseNode.first; I != links.end(); ++I)
			{
				links.erase(links.find(I.second));
			}
			links.erase(i);
		}
	}
	values.clear();
	values.resize(n);
	RNG.normal(values);
}

//----------------------------------------------------------------------

bool Network::add_link(const size_t& a, const size_t& b)
{
	if(a < size() and b < size() and a != b)
	{
		std::vector<size_t> neighbors_a(neighbors(a));
		bool bIsContain(false);
		
		if(!neighbors_a.empty())
		{
			for(size_t i(0); i < degree(a); ++i)
			{
				if(i == b)
				{
					bIsContain = true;
				}
			}
		}
		
		if(!bIsContain)
		{
			links.insert(std::pair<size_t, size_t> (a, b));
			links.insert(std::pair<size_t, size_t> (b, a));
			return true;
		}
	}
	
	return false;
}

//----------------------------------------------------------------------

size_t Network::random_connect(const double& mean_deg)
{
	links.clear();
	size_t counter(0);
	
	/*std::vector<int> poissonDegrees(size());
	RNG.poisson(poissonDegrees, mean_deg);
	
	std::vector<size_t> toBeLinkedNodes(0);
	for(size_t i(0); i < size(); ++i)
	{ toBeLinkedNodes.push_back(i); }
	
	for(size_t i(0); i < size(); ++i)
	{
		RNG.shuffle(toBeLinkedNodes);
		
		for(size_t j(0); j < toBeLinkedNodes.size(); ++j)
		{
			if(degree(i) < poissonDegrees[i])
			{
				if(degree(toBeLinkedNodes[j]) < poissonDegrees[toBeLinkedNodes[j]])
				{
					if(add_link(i, toBeLinkedNodes[j]))
					{
						counter += 2;
					}
				}
			} else { 
				break;
				}			
		} 
	}	
	return counter;*/
	
	for(size_t i(0); i < size(); ++i)
	{
		int rn(RNG.poisson(mean_deg));
		while(rn >= size())
		{
			rn = RNG.poisson(mean_deg);
		}
		
		if(degree(i) < rn)
		{
			int numberLinks(rn - degree(i));
			while(numberLinks > 0)
			{
				size_t m = size_t(RNG.uniform_double(0.0; size());
				if(add_link(i, m))
				{
					++counter;
					--numberLinks;
				}
			}
		}
	}
	return counter;
}

//----------------------------------------------------------------------

size_t Network::set_values(const std::vector<double>& newValues)
{
	size_t counter(0), n;
	
	if(size() < newValues.size()) 	{ n = size(); }
	else 							{ n = newValues.size(); }
	
	for(size_t i(0); i < n; ++i)
	{
		values[i] = newValues[i];
		++counter;
	}
	
	return counter;
	
}

//----------------------------------------------------------------------

size_t Network::size() const
{
	return values.size();
}

//----------------------------------------------------------------------

size_t Network::degree(const size_t &_n) const
{
	return neighbors(_n).size();
}

//----------------------------------------------------------------------

double Network::value(const size_t &_n) const
{
	return values[_n];
}

//----------------------------------------------------------------------

std::vector<double> Network::sorted_values() const
{
	std::vector<double> sorted_values(values);
	std::sort(sorted_values.begin(), sorted_values.end());
	std::reverse(sorted_values.begin(), sorted_values.end());
	
	return sorted_values;
}

//----------------------------------------------------------------------

std::vector<size_t> Network::neighbors(const size_t& node) const
{
	std::vector<size_t> _neighbors(0);
	if (node<size())
	{
		auto neigborsPairs = links.equal_range(node);
		for (auto I = neigborsPairs.first; I != neigborsPairs.second; ++I)
		{
			_neighbors.push_back(I->second);
		}
	}
	return _neighbors;
}
