{
    'targets': [{

        'target_name': 'cgal',

        'sources': [
            'src/cgal.cc',
            'src/AffTransformation2.cc',
            'src/Arrangement2.cc',
            'src/Arrangement2Face.cc',
            'src/Arrangement2Halfedge.cc',
            'src/Arrangement2Vertex.cc',
            'src/BBox2.cc',
            'src/Curve2.cc',
            'src/D2.cc',
            'src/Direction2.cc',
            'src/Line2.cc',
            'src/Point2.cc',
            'src/Polygon2.cc',
            'src/PolygonSet2.cc',
            'src/PolygonWithHoles2.cc',
            'src/Ray2.cc',
            'src/Segment2.cc',
            'src/Vector2.cc'
         ],

        'include_dirs': [
            '<!@(node -p "require(\'node-addon-api\').include")',
            '<!@(echo $CGAL_GYP_INCLUDES)'
        ],

        'dependencies': [
            '<!(node -p "require(\'node-addon-api\').gyp")'
        ],

        'defines': [
            '<!@(echo ${CGAL_USE_EPECK:+CGAL_USE_EPECK=$CGAL_USE_EPECK})'
        ],

        'conditions': [

            ['OS=="mac"', {
                'libraries': [ 'libgmp.a', 'libmpfr.a' ],
                'cflags+': ['-fvisibility=hidden'],
                'xcode_settings': {
                    'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                    'GCC_ENABLE_CPP_RTTI': 'YES',
                    'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # -fvisibility=hidden
                    'CLANG_CXX_LIBRARY': 'libc++',
                    'MACOSX_DEPLOYMENT_TARGET': '10.7',
                    'OTHER_CPLUSPLUSFLAGS': [
                        '-Wno-null-pointer-arithmetic',
                        '<!@(echo $CGAL_GYP_CXXFLAGS)'
                     ],
                    'OTHER_LDFLAGS': [ '<!@(echo $CGAL_GYP_LDFLAGS)' ]
                }
            }],

            ['OS=="linux"', {
                'cflags_cc!': [ '-fno-exceptions', '-fno-rtti' ],
                'cflags_cc': [
                    '-frounding-math',
                    '<!@(echo $CGAL_GYP_CXXFLAGS)'
                ],
                'libraries': [ '-lgmp', '-lmpfr' ],
                'ldflags': [ '<!@(echo $CGAL_GYP_LDFLAGS)', '-Bstatic ' ]
            }]

        ]

    }]
}
