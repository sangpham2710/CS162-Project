#include "SchoolYear.h"

std::ostream& operator<<(std::ostream& stream, const SchoolYear& schoolYear) {
  stream << schoolYear._id << '\n';
  stream << schoolYear.name << '\n';
  stream << schoolYear.pSemesters.size() << '\n';
  for (const auto& p : schoolYear.pSemesters) stream << p->_id << '\n';
  stream << schoolYear.pClasses.size() << '\n';
  for (const auto& p : schoolYear.pClasses) stream << p->_id << '\n';
  return stream;
}