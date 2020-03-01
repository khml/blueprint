//
// Created by KHML on 2020/01/19.
//

#ifndef BLUEPRINT_MACROLOGGER_HPP
#define BLUEPRINT_MACROLOGGER_HPP

#ifdef DEBUG2
#define LOG2(value) std::cerr << value << std::endl
#else
#define LOG2(value)
#endif

#endif //BLUEPRINT_MACROLOGGER_HPP
